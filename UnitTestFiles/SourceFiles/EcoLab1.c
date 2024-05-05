#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <stdio.h>
#include <stdlib.h>
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"

#include "IEcoLab1Events.h"
#include "IdEcoLab1.h"
#include "IdEcoList1.h"
#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"

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
	IEcoLab1* pIEcoLab2 = 0;
	IEcoCalculatorX* pIX = 0;
	IEcoCalculatorY* pIY = 0;

	/* Указатель на интерфейс контейнера точек подключения */
	IEcoConnectionPointContainer* pICPC = 0;  
	/* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP = 0;        
	/* Указатель на обратный интерфейс */
    IEcoLab1Events* pIEcoLab1Sink = 0;

    IEcoUnknown* pISinkUnk = 0;
    uint32_t cAdvise = 0;

	//int16_t a = 0;
	//int16_t b = 0;
	int32_t resultat = 0;
	char_t* name = 0;

	/* Секндомер */
	//clock_t start_time;

	/* Массивы для stooge sort */
    int* arr_int_stooge_sort; 
    //float* arr_float_stooge_sort;
	//double* arr_fdouble_stooge_sort;

	/* Массивы для qsort */
	//int* arr_int_qsort;
	//float* arr_float_qsort;
    //double* arr_double_qsort;

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

	/* Проверка поддержки подключений обратного интерфейса */
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void **)&pICPC);
    if (result != 0 || pICPC == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Запрос на получения интерфейса точки подключения */
    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1Events, &pICP);
    if (result != 0 || pICP == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	/* Освобождение интерфейса */
    pICPC->pVTbl->Release(pICPC);

    /* Создание экземпляра обратного интерфейса */
    result = createCEcoLab1Sink(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink);

    if (pIEcoLab1Sink != 0) {
        result = pIEcoLab1Sink->pVTbl->QueryInterface(pIEcoLab1Sink, &IID_IEcoUnknown,(void **)&pISinkUnk);
        if (result != 0 || pISinkUnk == 0) {
            /* Освобождение интерфейсов в случае ошибки */
            goto Release;
        }
        /* Подключение */
        result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
        /* Проверка */
        if (result == 0 && cAdvise == 1) {
            /* Сюда можно добавить код */
        }
        /* Освобождение интерфейса */
        pISinkUnk->pVTbl->Release(pISinkUnk);
    }

	//Демонстрация работы с интерфейсами

	/*a = 1;
	b = 1;

	pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
	resultat = 0;
	resultat = pIX->pVTbl->Addition(pIX, a, b);
	printf("%d + %d = %d\n\n", a, b, resultat);

	pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
	resultat = pIY->pVTbl->Division(pIY, a, b);
	printf("%d / %d = %d\n\n", a, b, resultat);

	pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
	resultat = pIX->pVTbl->Subtraction(pIX, a, b);
	printf("%d - %d = %d\n\n", a, b, resultat);

	pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
	resultat = pIY->pVTbl->Multiplication(pIY, a, b);
	printf("%d * %d = %d\n\n", a, b, resultat);

	pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void**)&pIEcoLab2);
	arr_int_stooge_sort = createArrInt(pIMem, 10);
	printArrInt(arr_int_stooge_sort, 10);
	pIEcoLab2->pVTbl->qsort(pIEcoLab1, (char*)arr_int_stooge_sort, 10, sizeof(int), compareInts);
	printArrInt(arr_int_stooge_sort, 10);
	printf("\n");*/

	// Конец демонстрации работы с интерфейсами

	printf("Input array size -> ");
	scanf_s("%d", &arr_size);

	arr_int_stooge_sort = createArrInt(pIMem, arr_size);
    /*arr_float_stooge_sort = createArrFloat(pIMem, arr_size);
    arr_fdouble_stooge_sort = createArrDouble(pIMem, arr_size);

    arr_int_qsort = createCopyArr(pIMem, arr_int_stooge_sort, arr_size * sizeof(int));
    arr_float_qsort = createCopyArr(pIMem, arr_float_stooge_sort, arr_size * sizeof(float));
    arr_double_qsort = createCopyArr(pIMem, arr_fdouble_stooge_sort, arr_size * sizeof(double));*/

	//printf("Before sort\n");
    //printArrInt(arr_int_stooge_sort, arr_size);
    //printArrFloat(arr_float_stooge_sort, arr_size);
    //printArrDouble(arr_fdouble_stooge_sort, arr_size);
    
	//start_time = clock();
	result = pIEcoLab1->pVTbl->qsort(pIEcoLab1, (char*)arr_int_stooge_sort, arr_size, sizeof(int), compareInts);
	/*printf("Stooge sort time (int): %fn\n", (double)(clock() - start_time)); 

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
    printf("Qsort time (double): %fn\n", (double)(clock() - start_time)); */


	printf("Sorted arrays\n");
	printArrInt(arr_int_stooge_sort, arr_size);
    //printArrFloat(arr_float_stooge_sort, arr_size);
    //printArrDouble(arr_fdouble_stooge_sort, arr_size);

    pIMem->pVTbl->Free(pIMem, arr_int_stooge_sort);
    /*pIMem->pVTbl->Free(pIMem, arr_float_stooge_sort);
    pIMem->pVTbl->Free(pIMem, arr_fdouble_stooge_sort);
    pIMem->pVTbl->Free(pIMem, arr_int_qsort);
    pIMem->pVTbl->Free(pIMem, arr_float_qsort);
    pIMem->pVTbl->Free(pIMem, arr_double_qsort);*/

	if (pIEcoLab1Sink != 0) {
        /* Отключение */
        result = pICP->pVTbl->Unadvise(pICP, cAdvise);
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pICP->pVTbl->Release(pICP);
    }

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

