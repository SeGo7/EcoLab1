#ifndef __C_ECOLAB1_H__
#define __C_ECOLAB1_H__

#include "IEcoLab1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

#include "IEcoLab1Events.h"
#include "IEcoEnumConnections.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab1ConnectionPoint.h"

typedef struct CEcoLab1 {

    /* Таблица функций интерфейса IEcoLab1 */
    IEcoLab1VTbl* m_pVTblIEcoLab1;

	/* Таблица функций интерфейса IEcoCalculatorX */
	IEcoCalculatorXVTbl* m_pVTblIEcoCalculatorX;

	/* Таблица функций интерфейса IEcoCalculatorY */
	IEcoCalculatorYVTbl* m_pVTblIEcoCalculatorY;

	/* Таблица функций интерфейса IEcoConnectionPointContainer */
    IEcoConnectionPointContainerVTbl* m_pVTblICPC;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

	/* Указатель на интерфейс IEcoCalculatorX включаемого компонента */
    IEcoCalculatorX* m_pIX;

	/* Указатель на интерфейс IEcoCalculatorY включаемого компонента */
    IEcoCalculatorY* m_pIY;

	/* Неделегирующий интерфейс IEcoUnknown */
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;

	/* Делегирующий IEcoUnknown, указывает на внешний
    или неделегирующий IEcoUnknown */
    IEcoUnknown* m_pIUnkOuter;

	/* Указатель на IEcoUnknown внутреннего компонента */
    IEcoUnknown* m_pInnerUnknown;

    /* Данные экземпляра */
    char_t* m_Name;

	/* Точка подключения */
    CEcoLab1ConnectionPoint* m_pISinkCP;

} CEcoLab1, *CEcoLab1Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1);

#endif /* __C_ECOLAB1_H__ */
