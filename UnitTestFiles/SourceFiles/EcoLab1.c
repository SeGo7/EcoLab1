/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2024 Sergey Goriachev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <stdio.h>
#include <stdlib.h>

// Вывод в консоль
void printArrInt(int* arr, size_t arr_size) {
    size_t i;
    printf("Size_el: int -> arr[");
	for (i = 0; i < arr_size; ++i) {
		printf("%d, ", arr[i]);
	}
	printf("]\n");
}

void printArrFloat(float* arr, size_t arr_size) {
    size_t i;
    printf("Size_el: float -> arr[");
	for (i = 0; i < arr_size; ++i) {
		printf("%f, ", arr[i]);
	}
	printf("]\n");
}

void printArrDouble(double* arr, size_t arr_size) {
    size_t i;
    printf("Size_el: double -> arr[");
	for (i = 0; i < arr_size; ++i) {
		printf("%lf, ", arr[i]);
	}
	printf("]\n");
}

// Генерация 
int* createArrInt(IEcoMemoryAllocator1 *pIMem, size_t arr_size) {
	int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, arr_size * sizeof(int));
	size_t i;
    for (i = 0; i < arr_size; ++i) {
        arr[i] = rand() % 30011 - 15000;
    }
    return arr;
}

float* createArrFloat(IEcoMemoryAllocator1 *pIMem, size_t arr_size)  {
    float *arr = (float *) pIMem->pVTbl->Alloc(pIMem, arr_size * sizeof(float));
	size_t i;
    for (i = 0; i < arr_size; ++i) {
        arr[i] = ((float) (rand() % 30011 - 15000 )) / ((float)(rand() % 100 + 1)) ;
    }
    return arr;
}

double* createArrDouble(IEcoMemoryAllocator1 *pIMem, size_t arr_size) {
    double *arr = (double *) pIMem->pVTbl->Alloc(pIMem, arr_size * sizeof(double));
	size_t i;
    for (i = 0; i < arr_size; ++i) {
        arr[i] = ((double) (rand() %30011 - 15000)) / ((float)(rand() % 100 + 1)) ;
    }
    return arr;
}

// Сравнение чисел
int __cdecl compareInts(const void* num1, const void* num2) {
    const int n1 = *(int*)num1;
    const int n2 = *(int*)num2;
    if (n1 == n2) return 0;
    else if (n1 > n2) return 1;
    else return -1;
}

int __cdecl compareInts16_t(const void* num1, const void* num2) {
    const int16_t n1 = *(int16_t*)num1;
    const int16_t n2 = *(int16_t*)num2;
    if (n1 == n2) return 0;
    else if (n1 > n2) return 1;
    else return -1;
}

int __cdecl compareInts32_t(const void* num1, const void* num2) {
    const int32_t n1 = *(int32_t*)num1;
    const int32_t n2 = *(int32_t*)num2;
    if (n1 == n2) return 0;
    else if (n1 > n2) return 1;
    else return -1;
}

int __cdecl compareDoubles(const void* num1, const void* num2) {
    const double n1 = *(double*)num1;
    const double n2 = *(double*)num2;
    if (n1 == n2) return 0;
    else if (n1 > n2) return 1;
    else return -1;
}


int __cdecl compareFloats(const void* num1, const void* num2) {
    const float n1 = *(float*)num1;
    const float n2 = *(float*)num2;
    if (n1 == n2) return 0;
    else if (n1 > n2) return 1;
    else return -1;
}

// Копирование массива
void *createCopyArr(IEcoMemoryAllocator1 *pIMem, void *src, uint32_t byte_count) {
    void *copy_array = pIMem->pVTbl->Alloc(pIMem, byte_count);
    pIMem->pVTbl->Copy(pIMem, copy_array, src, byte_count);
    return copy_array;
}

int16_t EcoMain(IEcoUnknown* pIUnk) {

    int16_t result = -1;

    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

	/* Секндомер */
	clock_t start_time;

	/* Массивы для stooge sort */
    int* arr_int_stooge_sort; 
    float* arr_float_stooge_sort;
	double* arr_fdouble_stooge_sort;

	/* Массивы для qsort */
	int* arr_int_qsort;
	float* arr_float_qsort;
    double* arr_double_qsort;

	/* Размер массива сравнения */
	size_t arr_size = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }


	printf("Input array size -> ");
	scanf_s("%d", &arr_size);


	arr_int_stooge_sort = createArrInt(pIMem, arr_size);
    arr_float_stooge_sort = createArrFloat(pIMem, arr_size);
    arr_fdouble_stooge_sort = createArrDouble(pIMem, arr_size);

    arr_int_qsort = createCopyArr(pIMem, arr_int_stooge_sort, arr_size * sizeof(int));
    arr_float_qsort = createCopyArr(pIMem, arr_float_stooge_sort, arr_size * sizeof(float));
    arr_double_qsort = createCopyArr(pIMem, arr_fdouble_stooge_sort, arr_size * sizeof(double));

	//printf("Before sort\n");
    //printArrInt(arr_int_stooge_sort, arr_size);
    //printArrFloat(arr_float_stooge_sort, arr_size);
    //printArrDouble(arr_fdouble_stooge_sort, arr_size);
    
	start_time = clock();
	result = pIEcoLab1->pVTbl->qsort(pIEcoLab1, (char*)arr_int_stooge_sort, arr_size, sizeof(int), compareInts);
	printf("Stooge sort time (int): %fn\n", (double)(clock() - start_time)); 

    start_time = clock();
    result = pIEcoLab1->pVTbl->qsort(pIEcoLab1, (char*)arr_float_stooge_sort, arr_size, sizeof(float), compareFloats);
	printf("Stooge sort time (float): %fn\n", (double)(clock() - start_time)); 

    start_time = clock();
    result = pIEcoLab1->pVTbl->qsort(pIEcoLab1, (char*)arr_fdouble_stooge_sort, arr_size, sizeof(double), compareDoubles);
    printf("Stooge sort time (double): %fn\n", (double)(clock() - start_time)); 

    start_time = clock();
    qsort(arr_int_qsort, arr_size, sizeof(int), compareInts);
    printf("Qsort time (int): %fn\n", (double)(clock() - start_time)); 

    start_time = clock();
    qsort(arr_float_qsort, arr_size, sizeof(float), compareFloats);
    printf("Qsort time (float): %fn\n", (double)(clock() - start_time)); 

    start_time = clock();
    qsort(arr_double_qsort, arr_size, sizeof(double), compareDoubles);
    printf("Qsort time (double): %fn\n", (double)(clock() - start_time)); 


	//printf("Sorted arrays\n");
	//printArrInt(arr_int_stooge_sort, arr_size);
    //printArrFloat(arr_float_stooge_sort, arr_size);
    //printArrDouble(arr_fdouble_stooge_sort, arr_size);

    pIMem->pVTbl->Free(pIMem, arr_int_stooge_sort);
    pIMem->pVTbl->Free(pIMem, arr_float_stooge_sort);
    pIMem->pVTbl->Free(pIMem, arr_fdouble_stooge_sort);
    pIMem->pVTbl->Free(pIMem, arr_int_qsort);
    pIMem->pVTbl->Free(pIMem, arr_float_qsort);
    pIMem->pVTbl->Free(pIMem, arr_double_qsort);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

