

#if !defined (PDUR_SM_H)
#define PDUR_SM_H

#include "Types_SwcServicePduR.hpp"
#include "CfgSwcServicePduR.hpp"
#include "SwcServicePduR_Lcfg.hpp"

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_SMDATAPLANEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Sm_Init(void);
#endif
#if(PDUR_SMDATAPLANEROM)

FUNC(void, PDUR_CODE) PduR_Sm_SrcFilter_LinearTaToSaCalculationStrategy(PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_SMDATAPLANEROM)

FUNC(void, PDUR_CODE) PduR_Sm_SrcFilter_SaTaFromMetaDataCalculationStrategy(PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_SMDATAPLANEROM)

FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_AddOffset(PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx, uint32 metaData);
#endif

#if(PDUR_SMDATAPLANEROM)

FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_SubtractOffset(PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx, uint32 metaData);
#endif

#if(PDUR_SMDATAPLANEROM)

FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_DestFilter_LinearTaToSaCalculationStrategy(PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_SMDATAPLANEROM)

FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_DestFilter_SaTaFromMetaDataCalculationStrategy(PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"
#endif

