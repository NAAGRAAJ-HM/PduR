

#define PDUR_SM_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Sm.hpp"
#include "SchM_PduR.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
LOCAL_INLINE FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx
   ,                                                                                             uint32 metaData);
#endif

#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)
LOCAL_INLINE FUNC(PduR_SmTaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx
   ,                                                                                             uint32 metaData);
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)
LOCAL_INLINE FUNC(uint32, PDUR_CODE) PduR_Sm_GetMetaData(P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, uint8 metaDataLength);
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Sm_UpdateFib(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmSaType sourceAdress, PduR_ConnectionIdOfSmSrcRomType learnedConnectionId);
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)
LOCAL_INLINE FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_CheckLearned(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmTaType targetAdress, PduR_ConnectionIdOfSmGDestRomType destConnection);
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Sm_Init(void){
  PduR_SmFibRamIterType smFibRamIdx;
  for(smFibRamIdx = 0; smFibRamIdx < PduR_GetSizeOfSmFibRam(); smFibRamIdx++){
    PduR_SetLearnedConnectionIdOfSmFibRam(smFibRamIdx, PDUR_SM_UNLEARNED_CONNECTION);
  }
}
#endif

#if(PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM == STD_ON)

FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_AddOffset(PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx, uint32 metaData){
  PduR_MaskOfSmLinearTaToSaCalculationStrategyRomType mask = PduR_GetMaskOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_OffsetOfSmLinearTaToSaCalculationStrategyRomType offset = PduR_GetOffsetOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_SmSaType sourceAdress = (metaData + offset) & mask;
  return sourceAdress;
}
#endif

#if(PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM == STD_ON)

FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_LinearTaToSaCalculationStrategy_GetSa_SubtractOffset(PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx, uint32 metaData){
  PduR_MaskOfSmLinearTaToSaCalculationStrategyRomType mask = PduR_GetMaskOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_OffsetOfSmLinearTaToSaCalculationStrategyRomType offset = PduR_GetOffsetOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_SmSaType sourceAdress = (metaData - offset) & mask;
  return sourceAdress;
}
#endif

#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)

LOCAL_INLINE FUNC(PduR_SmSaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx
   ,                                                                                             uint32 metaData){
  PduR_SaStartBitOfSmSaTaFromMetaDataCalculationStrategyRomType saStartBitPos = PduR_GetSaStartBitOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);
  PduR_SaMaskOfSmSaTaFromMetaDataCalculationStrategyRomType saMask = PduR_GetSaMaskOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);

  PduR_SmSaType sourceAdress = (metaData >> saStartBitPos) & saMask;
  return sourceAdress;
}
#endif

#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)

LOCAL_INLINE FUNC(PduR_SmTaType, PDUR_CODE) PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa(PduR_SmSaTaFromMetaDataCalculationStrategyRomIterType smSaTaFromMetaDataCalculationStrategyRomIdx
   ,                                                                                             uint32 metaData){
  PduR_TaStartBitOfSmSaTaFromMetaDataCalculationStrategyRomType taStartBitPos = PduR_GetTaStartBitOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);
  PduR_TaMaskOfSmSaTaFromMetaDataCalculationStrategyRomType taMask = PduR_GetTaMaskOfSmSaTaFromMetaDataCalculationStrategyRom(smSaTaFromMetaDataCalculationStrategyRomIdx);

  PduR_SmTaType targetAdress = (metaData >> taStartBitPos) & taMask;
  return targetAdress;
}
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)

LOCAL_INLINE FUNC(uint32, PDUR_CODE) PduR_Sm_GetMetaData(P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, uint8 metaDataLength){
  uint32 metaData = 0u;
  SduDataPtrType metaDataPtr = &info->SduDataPtr[info->SduLength - metaDataLength];
  uint8 itMetaData;
  for(itMetaData = metaDataLength; itMetaData > 0u; itMetaData--){
    metaData = (((uint32) (metaData << 8u)) | metaDataPtr[itMetaData - 1u]);
  }
  return metaData;
}
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Sm_UpdateFib(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmSaType sourceAdress, PduR_ConnectionIdOfSmSrcRomType learnedConnectionId){
  PduR_SmFibRamIterType smFibRamIdx = PduR_GetSmFibRamStartIdxOfSmDataPlaneRom(smDataPlaneIdx) + sourceAdress;
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  PduR_SetLearnedConnectionIdOfSmFibRam(smFibRamIdx, (PduR_LearnedConnectionIdOfSmFibRamType) learnedConnectionId);
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
}
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)

LOCAL_INLINE FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_CheckLearned(PduR_SmDataPlaneRomIterType smDataPlaneIdx, PduR_SmTaType targetAdress, PduR_ConnectionIdOfSmGDestRomType destConnection){
  PduR_FilterReturnType filterResult;
  PduR_SmFibRamIterType smFibRamIdx = PduR_GetSmFibRamStartIdxOfSmDataPlaneRom(smDataPlaneIdx) + targetAdress;
  PduR_LearnedConnectionIdOfSmFibRamType learnedConnectionId;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  learnedConnectionId = PduR_GetLearnedConnectionIdOfSmFibRam(smFibRamIdx);
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  if((learnedConnectionId == PDUR_SM_UNLEARNED_CONNECTION) ||
     (learnedConnectionId == destConnection)){
    filterResult = PDUR_FILTER_PASS;
  }
  else{
    filterResult = PDUR_FILTER_BLOCK;
  }
  return filterResult;
}
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Sm_SrcFilter_LinearTaToSaCalculationStrategy(PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_SmDataPlaneRomIterType smDataPlaneIdx = PduR_GetSmDataPlaneRomIdxOfSmSrcRom(smSrcRomIdx);
  PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx = PduR_GetSmLinearTaToSaCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneIdx);

  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmSrcRom(smSrcRomIdx));
  PduR_Sm_LinearTaToSaCalculationStrategy_GetSaFctPtrType getSaFctPtr =
    PduR_GetSmLinearTaToSaCalculationStrategyGetSaFctPtr(PduR_GetSmLinearTaToSaCalculationStrategyGetSaFctPtrIdxOfSmSrcRom(smSrcRomIdx));
  PduR_SmSaType sourceAdress = getSaFctPtr(smLinearTaToSaCalculationStrategyIdx, metaData);

  PduR_Sm_UpdateFib(smDataPlaneIdx, sourceAdress, PduR_GetConnectionIdOfSmSrcRom(smSrcRomIdx));
}
#endif

#if(PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM == STD_ON)

FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_DestFilter_LinearTaToSaCalculationStrategy(PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_SmDataPlaneRomIterType smDataPlaneIdx = PduR_GetSmDataPlaneRomIdxOfSmGDestRom(smGDestRomIdx);
  PduR_SmLinearTaToSaCalculationStrategyRomIterType smLinearTaToSaCalculationStrategyIdx = PduR_GetSmLinearTaToSaCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneIdx);

  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmGDestRom(smGDestRomIdx));
  PduR_MaskOfSmLinearTaToSaCalculationStrategyRomType mask = PduR_GetMaskOfSmLinearTaToSaCalculationStrategyRom(smLinearTaToSaCalculationStrategyIdx);
  PduR_SmTaType targetAdress = metaData & mask;

  return PduR_Sm_CheckLearned(smDataPlaneIdx, targetAdress, PduR_GetConnectionIdOfSmGDestRom(smGDestRomIdx));
}
#endif

#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Sm_SrcFilter_SaTaFromMetaDataCalculationStrategy(PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_SmDataPlaneRomIterType smDataPlaneRomIdx = PduR_GetSmDataPlaneRomIdxOfSmSrcRom(smSrcRomIdx);

  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmSrcRom(smSrcRomIdx));
  PduR_SmSaType sa = PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetSa(PduR_GetSmSaTaFromMetaDataCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneRomIdx), metaData);

  PduR_Sm_UpdateFib(smDataPlaneRomIdx, sa, PduR_GetConnectionIdOfSmSrcRom(smSrcRomIdx));
}
#endif

#if(PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM == STD_ON)

FUNC(PduR_FilterReturnType, PDUR_CODE) PduR_Sm_DestFilter_SaTaFromMetaDataCalculationStrategy(PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_SmDataPlaneRomIterType smDataPlaneRomIdx = PduR_GetSmDataPlaneRomIdxOfSmGDestRom(smGDestRomIdx);

  uint32 metaData = PduR_Sm_GetMetaData(info, PduR_GetMetaDataLengthOfSmGDestRom(smGDestRomIdx));
  PduR_SmSaType ta = PduR_Sm_SaTaFromMetaDataCalculationStrategy_GetTa(PduR_GetSmSaTaFromMetaDataCalculationStrategyRomIdxOfSmDataPlaneRom(smDataPlaneRomIdx), metaData);

  return PduR_Sm_CheckLearned(smDataPlaneRomIdx, ta, PduR_GetConnectionIdOfSmGDestRom(smGDestRomIdx));
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

