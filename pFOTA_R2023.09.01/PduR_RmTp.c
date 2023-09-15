

#define PDUR_RMTP_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Bm.hpp"
#include "PduR_Fm.hpp"
#include "PduR_Lock.hpp"
#include "PduR_RmTp.hpp"
#include "PduR_RmTp_TxInst.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_ThresholdReached(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx
   ,                                                                    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif

#if(PDUR_METADATA_SUPPORT == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReceptionQueueMetaData(PduR_RmSrcRomIterType rmSrcIdx
   ,                                                                                       PduR_BmTxBufferArrayRamIterType pduLength
   ,                                                                                       SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TriggerTransmissionOfDestinations(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_Init(void){
  {
    PduR_RmGDestTpTxStateRamIterType rmGDestTpTxStateRamTpIdx;
    for(rmGDestTpTxStateRamTpIdx = 0u; rmGDestTpTxStateRamTpIdx < PduR_GetSizeOfRmGDestTpTxStateRam(); rmGDestTpTxStateRamTpIdx++){
      PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(rmGDestTpTxStateRamTpIdx, PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
    }
  }
  {
    PduR_RmBufferedTpPropertiesRomIterType rmBufferedTpPropertiesRamIdx;
    for(rmBufferedTpPropertiesRamIdx = 0u; rmBufferedTpPropertiesRamIdx < PduR_GetSizeOfRmBufferedTpPropertiesRam(); rmBufferedTpPropertiesRamIdx++){
      PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRamIdx, PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);
      PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesRamIdx, PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM);
    }
  }
}
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx)){
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

      if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx))
      {
        PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx);
        PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, TRUE);

        retVal = PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);
        if(retVal != E_OK)
        {
          PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
        }
      }
    }
    else
#endif
    {
      retVal = PduR_GetLoTpTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);

  return retVal;
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result){
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK){
#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
#endif

      switch(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
      {
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        case PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM:
          PduR_RmTp_TxInst_TxConfirmation(rmGDestRomIdx, result);
          break;
#endif
#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
        case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
        {
          PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
          PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx), result);
        }
          break;
#endif
        default:
          break;
      }
    }
    else{
      PduR_Det_ReportError(PDUR_RMTP_MULTIPLESOURCEHANDLER_TPTXCONFIRMATION, PDUR_E_UNEXPECTED_CALL);
    }
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
}
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                             P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr){
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK){
#if(PDUR_RPGROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
#endif
      {
        switch(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
        {
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          case PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM:
            if((retry == NULL_PTR) || (retry->TpDataState != TP_DATARETRY))
            {
              retVal = PduR_RmTp_CopyTxData(rmGDestRomIdx, info, retry, availableDataPtr);
            }
            break;
#endif
#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
          case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          {
            PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpCopyTxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx), info, retry, availableDataPtr);
          }
            break;
#endif
          default:
            break;
        }
      }
    }
    else{
      PduR_Det_ReportError(PDUR_RMTP_MULTIPLESOURCEHANDLER_COPYTXDATA, PDUR_E_UNEXPECTED_CALL);
    }
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
  return retVal;
}
#endif

#if((PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx)){
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_RmDestRomIterType lastTxdRmDestRomIdx;
      Std_ReturnType foundSrcPdu = PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &lastTxdRmDestRomIdx);

      if(PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx) && (foundSrcPdu == E_OK) && (rmDestRomIdx == lastTxdRmDestRomIdx))
      {
        retVal = PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));
      }
      else
      {
        PduR_Det_ReportError(PDUR_RMTP_MULTIPLESOURCEHANDLER_CANCELTRANSMIT, PDUR_E_UNEXPECTED_CALL);
      }
    }
    else
#endif
    {
      retVal = PduR_GetLoTpCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_Transmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_RmDestRomIterType rmDestIdx;

  for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++){
    PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
    if(PduR_GetDirectionOfRmGDestRom(rmGDestRomIdx) == PDUR_TX_DIRECTIONOFRMGDESTROM){
#if(PDUR_RPGROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))
#endif
      {
        retVal &= PduR_RmTp_MultipleSourceHandler_Transmit(rmDestIdx, info);
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(info);
  return retVal;
}
#endif

#if(PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_Init_DedicatedTxBuffer(void){
  PduR_RmSrcRomIterType rmSrcRomIdx;
  for(rmSrcRomIdx = 0; rmSrcRomIdx < PduR_GetSizeOfRmSrcRom(); rmSrcRomIdx++){
    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx)){
      PduR_RmBufferedTpPropertiesRomIdxOfRmSrcRomType rmBufferedTpPropertiesIdx = PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcRomIdx);

      if(PduR_IsDedicatedTxBufferOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesIdx))
      {
        PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(rmBufferedTpPropertiesIdx);
        PduR_FmFifoElementRamIterType possilbeFmFifoElementRamIdx;
        for(possilbeFmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); possilbeFmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx);
            possilbeFmFifoElementRamIdx++)
        {
          PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0u;
          if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK)
          {
            PduLengthType bufferSizePtr = 0u;
            PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0u;

            PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(rmBufferedTpPropertiesIdx, fmFifoElementRamIdx);

            if(PduR_Bm_AllocateTxBuffer(fmFifoRomIdx, fmFifoElementRamIdx, 0u, 0u, &bufferSizePtr, &allocatedTxBufferIdxPtr, TRUE) == BUFREQ_OK)
            {
              PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
              PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);
              PduR_SetDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx, TRUE);
            }
            else
            {
              PduR_Det_ReportError(PDUR_RMTP_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
            }
          }
          else
          {
            PduR_Det_ReportError(PDUR_RMTP_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
          }
        }
      }
    }
  }
}
#endif

#if(PDUR_HASTPTXBUFFEREDFORWARDINGOFGENERALPROPERTIESROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_UpStartOfReception(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retval = E_NOT_OK;
  PduLengthType bufferSizePtr = 0u;
  PduLengthType availableDataPtr = 0u;
  PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
  {
    PduInfoType tempInfo;
    tempInfo.SduLength = info->SduLength;
    tempInfo.SduDataPtr = info->SduDataPtr;

    if(BUFREQ_OK == PduR_RmTp_StartOfReception(rmSrcIdx, &tempInfo, tempInfo.SduLength, &bufferSizePtr)){
      if(tempInfo.SduLength <= bufferSizePtr)
      {
        PduInfoType copyInfo;
        PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
        PduR_BmTxBufferRomIterType txBufferElementIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx);

        if(BUFREQ_OK == PduR_Bm_PutDataAsPtr(txBufferElementIdx, &copyInfo))
        {
          copyInfo.SduLength = info->SduLength;
          if(BUFREQ_OK == PduR_GetUpTpCopyTxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), &copyInfo, (P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA)) NULL_PTR, &availableDataPtr))
          {
            if(availableDataPtr == 0u)
            {
              PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_OK);
              PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_OK);
              retval = E_OK;
            }
            else
            {
              PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_NOT_OK);
              PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);
            }
          }
          else
          {
            PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_NOT_OK);
            PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);
          }
        }
        else
        {
          PduR_RmTp_TpRxIndication((PduR_RmSrcRomIdxOfRxTp2DestType) rmSrcIdx, E_NOT_OK);
          PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);
        }
      }
      else
      {
        PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);
      }
    }
    else{
      PduR_GetUpTpTpTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), E_NOT_OK);
    }
  }
  PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(availableDataPtr);
  return retval;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception(PduR_RmSrcRomIterType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                             PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;

#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(bufferSizePtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
#if(PDUR_METADATA_SUPPORT == STD_ON)
  else if((PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) && ((info == NULL_PTR) || (info->SduDataPtr == NULL_PTR) || (info->SduLength < (PduLengthType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))))){
    errorId = PDUR_E_PARAM_POINTER;
  }
#endif
  else
#endif
  {
    PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
    {
      retVal = PduR_GetFctPtrOfRmTp_StartOfReception_TpRxSmStateHandler(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) (rmSrcIdx, info, TpSduLength, bufferSizePtr);
    }
    PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
  }
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_RMTP_SORX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
  return retVal;
}
#endif

#if(PDUR_METADATA_SUPPORT == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReceptionQueueMetaData(PduR_RmSrcRomIterType rmSrcIdx
   ,                                                                                       PduR_BmTxBufferArrayRamIterType pduLength
   ,                                                                                       SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  PduR_BmTxBufferArrayRamIterType pduLengthIntern = pduLength;
  BufReq_ReturnType retVal;
  PduR_BmTxBufferArrayRamIterType metadataStartPosition =
    pduLengthIntern - (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx);

  pduLengthIntern = (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));

  retVal = PduR_Bm_PutData((PduR_BmTxBufferRomIterType) bmTxBufferRomIdx, pduLengthIntern, &sduDataPtr[metadataStartPosition]);
  *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(bmTxBufferRomIdx);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                       P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;

#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(info == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if((info->SduLength > 0u) && (info->SduDataPtr == NULL_PTR)){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(bufferSizePtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
#endif
  {
    PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
    {
      retVal = PduR_GetFctPtrOfRmTp_CopyRxData_TpRxSmStateHandler(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) ((PduR_RmSrcRomIterType) rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr);
    }
    PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_RMTP_CPYRX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_RmSrcRomIterType rmSrcIdx){
  PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx;
  PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx);
  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++){
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM){
      PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
      PduR_Bm_AssignAssociatedBuffer2DestinationInstance(bmTxBufferRomIdx, bmTxBufferInstanceRomIdx);
      PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), bmTxBufferInstanceRomIdx);
      bmTxBufferInstanceRomIdx++;
    }
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, Std_ReturnType result){
  PduR_Lock_LockRoutingPathBySrcPdu(rmSrcIdx);
  {
    PduR_GetFctPtrOfRmTp_TpRxIndication_TpRxSmStateHandler(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) ((PduR_RmSrcRomIterType) rmSrcIdx, result);
  }
  PduR_Lock_UnlockRoutingPathBySrcPdu(rmSrcIdx);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx
   ,                                                                    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr){
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;

#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(info == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if((info->SduLength > 0u) && (info->SduDataPtr == NULL_PTR)){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(availableDataPtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
#endif
  {
    PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
    {
      retVal = PduR_RmTp_TxInst_CopyTxData(rmGDestRomIdx, info, retry, availableDataPtr);
    }
    PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
    PDUR_DUMMY_STATEMENT(retry);
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_RMTP_CPYTX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_ThresholdReached(PduR_RmSrcRomIterType rmSrcIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_BmTxBufferArrayRamIterType availableTotalDataSize = PduR_Bm_GetLinearDataSize(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));

#if(PDUR_METADATA_SUPPORT == STD_ON )
  if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))){
    availableTotalDataSize -= (PduR_BmTxBufferArrayRamIterType) PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  }
#endif

  if(availableTotalDataSize >= PduR_GetTpThresholdOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))){
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TriggerTransmissionOfDestinations(PduR_RmSrcRomIterType rmSrcIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_RmDestRomIterType rmDestRomIdx;

  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++){
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM){
#if(PDUR_RPGROM == STD_ON)
      if((PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) && (0u == PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
      {
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
        PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
        PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
        PduR_SetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TXINST_IDLE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM);
        PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx);
        PduR_DecPendingConfirmationsOfFmFifoRam(fmFifoRomIdx);
        PduR_GetFctPtrOfRmTp_FinishTransmission_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmGDestRomIdx, E_NOT_OK);
        retVal &= E_NOT_OK;
      }
      else
#endif
      {
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
        if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
        {
          PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

          if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx))
          {
            PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx);
            PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, TRUE);

            retVal &= PduR_RmTp_TxInst_TriggerTransmit(rmDestRomIdx, rmGDestRomIdx);
            if(E_OK != retVal)
            {
              PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
            }
          }
        }
        else
#endif
        {
          retVal &= PduR_RmTp_TxInst_TriggerTransmit(rmDestRomIdx, rmGDestRomIdx);
        }
      }
    }
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE(PduR_RmSrcRomIterType rmSrcIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx);

  if(PduR_RmTp_ThresholdReached(rmSrcIdx) == E_OK){
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
    PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, PduR_GetQueuedDestCntOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));

    PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx), rmSrcIdx);
    PduR_GetFctPtrOfFm_ActivateRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx);

    retVal = PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx);
    if(retVal != E_OK){
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
    }
  }
  else{
    retVal = E_OK;
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));

  if(fmFifoElementRamWriteIdx == fmFifoElementRamReadIdx){
    if(PduR_RmTp_ThresholdReached(rmSrcIdx) == E_OK){
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
      PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, PduR_GetQueuedDestCntOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));

      PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx), rmSrcIdx);
      PduR_GetFctPtrOfFm_ActivateRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx);

      retVal = PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx);
      if(retVal != E_OK)
      {
        PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
      }
    }
    else{
      retVal = E_OK;
    }
  }
  else{
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction(PduR_RmSrcRomIterType rmSrcIdx){
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  return E_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_IDLE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);

  if(result == E_OK){
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
    PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx, PduR_GetQueuedDestCntOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));

    PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx), rmSrcIdx);
    PduR_GetFctPtrOfFm_ActivateRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx);

    if(PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx) != E_OK){
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);
    }
  }
  else{
    PduR_Det_ReportError(PDUR_FINISHRECEPTION, PDUR_E_FATAL);
  }
}

#endif
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));

  if(fmFifoElementRamWriteIdx == fmFifoElementRamReadIdx){
    if(result == E_OK){
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
      PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx, PduR_GetQueuedDestCntOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)));

      PduR_RmTp_AssignAssociatedBuffer2Destination(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx), rmSrcIdx);
      PduR_GetFctPtrOfFm_ActivateRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx);

      if(PduR_RmTp_TriggerTransmissionOfDestinations(rmSrcIdx) != E_OK)
      {
        PduR_GetFctPtrOfFm_FinishWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx)) (fmFifoElementRamWriteIdx, result);
        PduR_SetRmDestRomIdxOfFmFifoElementRam((fmFifoElementRamWriteIdx), PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);
        PduR_Fm_ActivateNext(fmFifoRomIdx);
      }
    }
    else{
      PduR_GetFctPtrOfFm_FinishWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx)) (fmFifoElementRamWriteIdx, result);
      PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM);
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);
      PduR_SetRmDestRomIdxOfFmFifoElementRam((fmFifoElementRamWriteIdx), PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);
      PduR_Fm_ActivateNext(fmFifoRomIdx);
    }
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE_TPTXSMSTATEOFFMFIFORAM);
  if(result != E_OK){
    PduR_RmTp_CancelTransmitPreparation(fmFifoElementRamWriteIdx);
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfFm_FinishWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx)) (fmFifoElementRamWriteIdx, result);
  PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);
  PduR_SetRmDestRomIdxOfFmFifoElementRam((fmFifoElementRamWriteIdx), PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);
  PduR_Fm_ActivateNext(fmFifoRamIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM   == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_NoAction(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_CancelTransmitPreparation(PduR_FmFifoElementRamIterType fmFifoElementRamIdx){
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx));
  PduR_RmDestRomIterType rmDestRomIdx;
  for(rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestRomIdx++){
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM){
      PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
      if(PduR_GetTpTxInstSmStateOfRmGDestTpTxStateRam(PduR_GetRmGDestTpTxStateRamIdxOfRmGDestRom(rmGDestRomIdx)) == PDUR_RM_TXINST_ACTIVE_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM)
      {
        (void) PduR_RmTp_TxInst_CancelTransmit(rmGDestRomIdx);
      }
    }
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE(PduR_RmDestRomIterType rmGDestRomIdx, Std_ReturnType result){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  if(PduR_GetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx) == 0u){
    PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
    PduR_GetFctPtrOfFm_FinishRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx, result);
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);
    PduR_Fm_ActivateNext(fmFifoRomIdx);
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  if(PduR_GetPendingConfirmationsOfFmFifoRam(fmFifoRomIdx) == 0u){
    PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
    PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRomIdx, PDUR_RM_TX_TRANSMISSION_FINISHED_TPTXSMSTATEOFFMFIFORAM);
    PduR_GetFctPtrOfFm_FinishRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx)) (fmFifoElementRamTPReadIdx, result);
    if(result != E_OK){
      PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamTPReadIdx));
      PduR_GetFctPtrOfRmTp_CancelReceive_TpRxSmStateHandler(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) (rmSrcIdx);
    }
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError(PduR_RmDestRomIterType rmGDestRomIdx, Std_ReturnType result){
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE(PduR_RmSrcRomIterType rmSrcIdx
   ,                                                                                           P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType
   ,                                                                                                                                                                                  AUTOMATIC
   ,                                                                                                                                                                                  PDUR_APPL_DATA)
                                                                                            bufferSizePtr){
  BufReq_ReturnType retVal = BUFREQ_OK;

  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0u;
  if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK){
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0u;
    PduLengthType metaDataLength = 0u;

#if  (PDUR_METADATA_SUPPORT == STD_ON )
    if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))){
      metaDataLength = PduR_GetMetaDataLengthOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
    }
#endif

    PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx);

    PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), fmFifoElementRamIdx);

    PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx));

    if(PduR_Bm_AllocateTxBuffer(fmFifoRomIdx, fmFifoElementRamIdx, TpSduLength, metaDataLength, bufferSizePtr, &allocatedTxBufferIdxPtr, TRUE) == BUFREQ_OK){
      PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);
#if  (PDUR_METADATA_SUPPORT == STD_ON )
      if(PduR_IsMetaDataLengthUsedOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx)))
      {
        retVal = PduR_RmTp_StartOfReceptionQueueMetaData(rmSrcIdx, info->SduLength, info->SduDataPtr, bufferSizePtr);
      }
      if(retVal != BUFREQ_OK)
      {
        PduR_Det_ReportError(PDUR_RXSM_STARTOFRECEPTION, PDUR_E_FATAL);
      }
      else
#endif
      {
        PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_ACTIVE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);
        PduR_GetFctPtrOfFm_ActivateWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);

        if((PduR_GetFctPtrOfRmTp_CheckReady2Transmit_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmSrcIdx)) != E_OK)
        {
          PduR_GetFctPtrOfRmTp_TpRxIndication_TpRxSmStateHandler(PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx))) (rmSrcIdx, E_NOT_OK);
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
    else{
      PduR_Fm_FreeFifoElement(fmFifoRomIdx, fmFifoElementRamIdx);
      retVal = BUFREQ_E_NOT_OK;
    }
  }
  else{
    retVal = BUFREQ_E_NOT_OK;
  }
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(info);
  PDUR_DUMMY_STATEMENT(TpSduLength);
  PDUR_DUMMY_STATEMENT(bufferSizePtr);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                                               PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  PduR_Det_ReportError(PDUR_FCT_SOR, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(info);
  PDUR_DUMMY_STATEMENT(TpSduLength);
  PDUR_DUMMY_STATEMENT(bufferSizePtr);
  return BUFREQ_E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength
   ,                                                                                       SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  BufReq_ReturnType retVal;

  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_BmTxBufferRomIterType txBufferElementIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx);

  retVal = PduR_Bm_PutData(txBufferElementIdx, (PduR_BmTxBufferArrayRamIterType) pduLength, sduDataPtr);

  if(retVal == BUFREQ_OK){
    PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
    if(PduR_GetFctPtrOfRmTp_CheckReady2Transmit_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmSrcIdx) != E_OK){
      retVal = BUFREQ_E_NOT_OK;
    }
  }
  *bufferSizePtr = (PduLengthType) PduR_Bm_GetTotalBufferSize(txBufferElementIdx);
  return retVal;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength
   ,                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(pduLength);
  PDUR_DUMMY_STATEMENT(sduDataPtr);
  PDUR_DUMMY_STATEMENT(bufferSizePtr);
  return BUFREQ_E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength
   ,                                                                                         SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  PduR_Det_ReportError(PDUR_RXSM_COPYRXDATA_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(pduLength);
  PDUR_DUMMY_STATEMENT(sduDataPtr);
  PDUR_DUMMY_STATEMENT(bufferSizePtr);
  return BUFREQ_E_NOT_OK;
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfRmTp_FinishReception_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRomIdx)) (rmSrcIdx, result);
  PduR_GetFctPtrOfFm_FinishWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx)) (fmFifoElementRamWriteIdx, result);
  PduR_SetFmFifoElementRamIdxOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_NO_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM);
  PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_IDLE_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result){
  PduR_Det_ReportError(PDUR_RMTP_RXSM_TPRXINDICATION_UNEXPECTEDCALL, PDUR_E_UNEXPECTED_CALL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx){
  PduR_SetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx), PDUR_RM_RX_ABORTED_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx){
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx){
  PduR_Det_ReportError(PDUR_RXSM_TPCANCELRECEIVE_FATALERROR, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

