

#define PDUR_RMTP_TXINST_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Bm.hpp"
#include "PduR_RmTp_TxInst.hpp"
#include "PduR_Lock.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoAndUpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_UPTPOFMMROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_UpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoTransmit(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_UPTPOFMMROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_UpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx){
  Std_ReturnType retVal = E_NOT_OK;
  BufReq_ReturnType retValBufReq;
  PduLengthType bufferSizePtr = 0u;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx));

  {
#if(PDUR_METADATA_SUPPORT == STD_ON )
    if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))){
      PduInfoType metaInfo;
      PduR_Bm_GetDataAsPtr(bmTxBufferInstanceRomIdx, &metaInfo, PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));

      retValBufReq = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &metaInfo, PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx), &bufferSizePtr);
    }
    else
#endif
    {
      retValBufReq = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), (P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA)) NULL_PTR, PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx), &bufferSizePtr);
    }
  }
  if(retValBufReq == BUFREQ_OK){
    if(bufferSizePtr < PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx)){
      PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);
    }
    else{
      PduInfoType info;

      PduR_Bm_GetDataAsPtr(bmTxBufferInstanceRomIdx, &info, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx));

      if(BUFREQ_OK == PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &info, &bufferSizePtr))
      {
        PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_OK);
        retVal = E_OK;
      }
      else
      {
        PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);
      }
    }
  }
  if(E_OK == retVal){
    PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, E_OK);
  }
  else{
    PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, E_NOT_OK);
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoTransmit(PduR_RmGDestRomIterType rmGDestRomIdx){
  Std_ReturnType retVal = E_NOT_OK;

  PduInfoType info;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx));

  PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, &info, PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx));
#if(PDUR_METADATA_SUPPORT == STD_ON)
  if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))){
    PduR_Bm_GetDataAsPtr(bmTxBufferInstanceRomIdx, &info, (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));
  }
#endif

  info.SduLength = PduR_Bm_GetTotalDataTranferredLength(bmTxBufferInstanceRomIdx);

  if(E_OK == PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &info)){
    retVal &= E_OK;
  }
  else{
    PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, E_NOT_OK);
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_LoAndUpTransmit(PduR_RmGDestRomIterType rmGDestRomIdx){
  Std_ReturnType retVal = E_NOT_OK;

  {
    if(PduR_GetDirectionOfRmGDestRom(rmGDestRomIdx) == PDUR_TX_DIRECTIONOFRMGDESTROM){
      retVal = PduR_RmTp_TxInst_LoTransmit(rmGDestRomIdx);
    }
#if(PDUR_UPTPOFMMROM == STD_ON)
    else{
      retVal = PduR_RmTp_TxInst_UpTransmit(rmGDestRomIdx);
    }
#endif
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx){
  return (PduR_GetPduR_RmTp_TxInst_TriggerTransmitOfRmTxInstSmRom(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)))[PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx)] (rmDestRomIdx, rmGDestRomIdx));
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_RmTxinstIdle(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
  PDUR_DUMMY_STATEMENT(rmDestRomIdx);
  return PduR_RmTp_TxInst_LoAndUpTransmit(rmGDestRomIdx);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_RmTxinstWaiting(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx){
  Std_ReturnType retVal = E_OK;
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
  PduR_EvC_WriteDeferredEventCache(rmDestRomIdx, (PduR_RmGDestRomIdxOfRmDestRomType) rmGDestRomIdx);
#endif
  PDUR_DUMMY_STATEMENT(rmDestRomIdx);

  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_FatalError(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_Det_ReportError(PDUR_RM_TPTRIGGERTRANSMIT_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmDestRomIdx);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  return E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr){
  return (PduR_GetPduR_RmTp_TxInst_CopyTxDataOfRmTxInstSmRom(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)))[PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx)] ((PduR_RmGDestRomIterType) rmGDestRomIdx, info->SduLength, info->SduDataPtr, retry, availableDataPtr));
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxinstActive(PduR_RmGDestRomIterType rmGDestRomIdx
   ,                                                                             PduLengthType pduLength
   ,                                                                             SduDataPtrType sduDataPtr
   ,                                                                             P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr){
  BufReq_ReturnType retVal;

  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));

  retVal = PduR_Bm_GetData(bmTxBufferInstanceRomIdx, (PduR_BmTxBufferArrayRamIterType) pduLength, sduDataPtr);
  *availableDataPtr = (PduLengthType) PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx);

  PDUR_DUMMY_STATEMENT(retry);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxinstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength
   ,                                                                              SduDataPtrType sduDataPtr
   ,                                                                              P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC
   ,                                                                                                                                             PDUR_APPL_DATA) availableDataPtr){
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  PDUR_DUMMY_STATEMENT(pduLength);
  PDUR_DUMMY_STATEMENT(sduDataPtr);
  PDUR_DUMMY_STATEMENT(retry);
  PDUR_DUMMY_STATEMENT(availableDataPtr);
  return BUFREQ_E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength
   ,                                                                             SduDataPtrType sduDataPtr
   ,                                                                             P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr){
  PduR_Det_ReportError(PDUR_RMTP_TXINSTSM_COPYTXDATA_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  PDUR_DUMMY_STATEMENT(pduLength);
  PDUR_DUMMY_STATEMENT(sduDataPtr);
  PDUR_DUMMY_STATEMENT(retry);
  PDUR_DUMMY_STATEMENT(availableDataPtr);
  return BUFREQ_E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result){
  PduR_GetPduR_RmTp_TxInst_TxConfirmationOfRmTxInstSmRom(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)))[PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx)] ((PduR_RmGDestRomIterType) rmGDestRomIdx, result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_RmTxinstActiveOrRmTxinstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
  PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx);
  PduR_DecPendingConfirmationsOfFmFifoRam(fmFifoRomIdx);
  PduR_GetFctPtrOfRmTp_FinishTransmission_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmGDestRomIdx, result);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result){
  PduR_Det_ReportError(PDUR_RMTP_TXINSTSM_TPTXCONFIRMATION_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit(PduR_RmDestRomIterType rmGDestRomIdx){
  return (PduR_GetPduR_RmTp_TxInst_CancelTransmitOfRmTxInstSmRom(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)))[PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx)] (rmGDestRomIdx));
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_FatalError(PduR_RmDestRomIterType rmGDestRomIdx){
  PduR_Det_ReportError(PDUR_RMTP_TXINSTSM_TPCANCELTRANSMIT_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  return E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_RmTxinstActive(PduR_RmDestRomIterType rmGDestRomIdx){
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ABORTED_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
  return E_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_RmTxinstWaiting(PduR_RmDestRomIterType rmGDestRomIdx){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
  PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx);
  PduR_DecPendingConfirmationsOfFmFifoRam(fmFifoRomIdx);
  PduR_GetFctPtrOfRmTp_FinishTransmission_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmGDestRomIdx, E_NOT_OK);
  return E_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_RmTxinstAborted(PduR_RmDestRomIterType rmGDestRomIdx){
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  return E_OK;
}
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_MainFunction(PduR_RmGDestRomIterType rmGDestRomIdx){
  if((PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx) == PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM) && (PDUR_RM_TXINST_WAITING_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM == PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)))){
    PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
    {
      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
      (void) PduR_RmTp_TxInst_LoAndUpTransmit(rmGDestRomIdx);
    }
    PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
  }
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

