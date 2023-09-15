

#define PDUR_RMIF_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Fm.hpp"
#include "PduR_McQ.hpp"
#include "PduR_Lock.hpp"
#include "PduR_RmIf.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))
#define PduR_Core_MemCpyRomToRam(d, s, l)    VStdMemCpyRomToRam((d), (s), (l))

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_RmIf_TruncateDlc(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_FifoHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON )

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationNoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Forward2Buffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_SingleBufferHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if( (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, boolean useLock);
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_TriggerTransmit(PduR_RmDestRomIterType rmDestIdx, CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessNoBufferedGwRouting(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessBufferedRouting(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx, PduR_RmGDestRomIterType rmGDestRomIdx
   ,                                                                             P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

#if((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Remove(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_DEFERREDEVENTCACHEROM == STD_ON))

LOCAL_INLINE FUNC(uint16, PDUR_CODE) PduR_QAL_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Flush(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmIf_SingleBuffer_Init(void){
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0u; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++){
    if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx) && PduR_IsSingleBufferRomUsedOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))){
      PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_SingleBufferRomIdxOfRmBufferedIfPropertiesRomType singleBufferRomIdx = PduR_GetSingleBufferRomIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx);

      PduR_Core_MemCpyRomToRam(PduR_GetAddrSingleBufferArrayRam(PduR_GetSingleBufferArrayRamStartIdxOfSingleBufferRom(singleBufferRomIdx)), PduR_GetAddrSingleBufferInitValuesRom(PduR_GetSingleBufferInitValuesRomStartIdxOfSingleBufferRom(singleBufferRomIdx)), PduR_GetSingleBufferArrayRamLengthOfSingleBufferRom(singleBufferRomIdx));
      PduR_SetActualLengthOfSingleBufferRam(singleBufferRomIdx, PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx));
    }
  }
}
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmIf_InitDestPduState(void){
  PduR_RmBufferedIfPropertiesRomIterType rmBufferedIfPropertiesRamIdx;
  for(rmBufferedIfPropertiesRamIdx = 0u; rmBufferedIfPropertiesRamIdx < PduR_GetSizeOfRmBufferedIfPropertiesRam(); rmBufferedIfPropertiesRamIdx++){
#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    if(PduR_IsSingleBufferRomUsedOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRamIdx)){
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRamIdx, PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
    }
#endif
#if((PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
    else
#endif
#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON){
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRamIdx, PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
    }
#endif
  }
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, boolean useLock){
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
        PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, useLock);

        retVal = PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);
        if(retVal != E_OK)
        {
          PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
        }
      }
    }
    else
#endif
    {
      retVal = PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);

  PDUR_DUMMY_STATEMENT(useLock);
  return retVal;
}
#endif

#if((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK){
#if(PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM)
      {
        retVal = PduR_RmIf_TriggerTransmit(rmDestRomIdx, info);
      }
      else
#endif
#if(PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON)
      if(PduR_IsTriggerTransmitSupportedOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)))
      {
        retVal = PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx))) (PduR_GetSrcHndOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)), info);
      }
      else
#endif
      {
        PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT, PDUR_E_PDU_ID_INVALID);
      }
    }
    else{
      PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT, PDUR_E_PDU_ID_INVALID);
    }
  }
  return retVal;
}
#endif

#if((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx)){
      PduR_RmDestRomIterType lastTxdRmDestRomIdx;
      Std_ReturnType foundSrcPdu = PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &lastTxdRmDestRomIdx);

      if(PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx)) && (foundSrcPdu == E_OK) && (rmDestRomIdx == lastTxdRmDestRomIdx))
      {
        retVal = PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));
      }
      else
      {
        PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_CANCELTRANSMIT, PDUR_E_UNEXPECTED_CALL);
      }
    }
    else
#endif
    {
      retVal = PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
  return retVal;
}
#endif

#if(PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx){
  PduR_RmDestRomIterType rmDestRomIdx;

  if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK){
#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)

    PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
#endif
#if((PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON) && ((PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) || ((PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && (PDUR_MCQBUFFERROM == STD_ON))))
    {
      PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);

      if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcRomIdx))
      {
        switch(PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx))
        {
#if(PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)

          case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
            PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx));
            break;
#endif
#if((PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && (PDUR_MCQBUFFERROM == STD_ON))

          case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) != PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM)
#endif
            {
              PduR_CoreManagerRomIdxOfMmRomType destCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)));
              PduR_CoreManagerRomIdxOfMmRomType srcCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx));

              if(PduR_McQ_WriteTxConfirmation(PduR_GetMcQBufferRomIdxOfSrcCoreRom(PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(destCoreIdx) + srcCoreIdx), rmSrcRomIdx) == E_NOT_OK)
              {
                PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_MCQ_QUEUE_OVERFLOW);
              }
            }
            break;
#endif
          default:

            break;
        }
      }
    }
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)

    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM){
      PduR_RmIf_TxConfirmation(rmGDestRomIdx);
    }
#endif
  }
  else{
    PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_TXCONFIRMATION, PDUR_E_PDU_ID_INVALID);
  }
}
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_SingleBufferHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  (void) PduR_QAL_Put(rmGDest, rmDest, info->SduLength, info->SduDataPtr);

  switch(PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest)){
#if(PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
    {
      PduInfoType queuedPduInfo;
      PduR_RmDestRomIterType rmDestRomIdx;

      if(PduR_QAL_Get(rmGDest, &rmDestRomIdx, &queuedPduInfo) == E_OK)
      {
        if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &queuedPduInfo, FALSE))
        {
          PduR_Det_ReportError(PDUR_RMIF_SINGLEBUFFERHANDLING, PDUR_E_PDU_INSTANCES_LOST);
        }
      }
      break;
    }
#endif
#if(PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
    {
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
      PduR_EvC_WriteDeferredEventCache(rmDest, rmGDest);
#endif
      break;
    }
#endif
    default:

      break;
  }

  PDUR_DUMMY_STATEMENT(rmDest);
}
#endif

#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_FifoHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  boolean triggerTransmission = TRUE;

  if(PduR_QAL_Put(rmGDest, rmDest, info->SduLength, info->SduDataPtr) != E_OK){
    PduR_QAL_Flush(rmGDest);
    PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
    PduR_Det_ReportError(PDUR_FCT_RMIF_FQ, PDUR_E_PDU_INSTANCES_LOST);

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    PduR_Rm_MultipleSourceHandler_Reset(rmGDest);
#endif

#if(PDUR_ERROR_NOTIFICATION == STD_ON)
    ErrorNotificationQueueOverflow(PduR_GetDestHndOfRmGDestRom(rmGDest));
#endif

    if(PduR_QAL_Put(rmGDest, rmDest, info->SduLength, info->SduDataPtr) != E_OK){
      triggerTransmission = FALSE;
    }
  }

  if((triggerTransmission == TRUE) && (PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest)) == PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM)){
    switch(PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest)){
#if(PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
      case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:
      {
        PduInfoType destPduInfo;
        PduR_RmDestRomIterType rmDestRomIdx;
        PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest);

        if(PduR_QAL_Get(rmGDest, &rmDestRomIdx, &destPduInfo) == E_OK)
        {
          if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE))
          {
            PduR_QAL_Flush(rmGDest);
            PduR_Det_ReportError(PDUR_FCT_RMIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
          }
          else
          {
            PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
          }
        }
        break;
      }
#endif
#if(PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
      case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
      {
#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
        if(PduR_QAL_GetFillLevel(rmGDest) == 1u)
        {
          PduR_EvC_WriteDeferredEventCache(rmDest, rmGDest);
        }
#endif
        break;
      }
#endif
      default:

        break;
    }
  }
}
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_SingleBuffer_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr){
  PduR_SingleBufferRomIdxOfRmBufferedIfPropertiesRomType singleBufferRomIdx = PduR_GetSingleBufferRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  PduR_Core_MemCpyRamToRam(PduR_GetAddrSingleBufferArrayRam(PduR_GetSingleBufferArrayRamStartIdxOfSingleBufferRom(singleBufferRomIdx)), sduDataPtr, pduLength);
  PduR_SetActualLengthOfSingleBufferRam(singleBufferRomIdx, pduLength);

  PDUR_DUMMY_STATEMENT(rmDestRomIdx);
  return E_OK;
}
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_SingleBuffer_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_SingleBufferRomIdxOfRmBufferedIfPropertiesRomType singleBufferRomIdx = PduR_GetSingleBufferRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  info->SduDataPtr = PduR_GetAddrSingleBufferArrayRam(PduR_GetSingleBufferArrayRamStartIdxOfSingleBufferRom(singleBufferRomIdx));
  info->SduLength = PduR_GetActualLengthOfSingleBufferRam(singleBufferRomIdx);
  *rmDestRomIdx = PduR_GetRmDestRomIdxOfSingleBufferRom(singleBufferRomIdx);
  return E_OK;
}
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationNoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_Lock_LockRoutingPathByDestPdu(rmDestIdx);
  if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestIdx, info, FALSE)){
    PduR_Det_ReportError(PDUR_FCT_RMIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestIdx);
}
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Forward2Buffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduR_RmGDestRomIdxOfRmDestRomType rmGDest = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
  PduInfoType destPduInfo;
  PduR_Lock_LockRoutingPathByDestPdu(rmDestIdx);
  destPduInfo.SduDataPtr = info->SduDataPtr;
  destPduInfo.SduLength = PduR_RmIf_TruncateDlc(rmGDest, info);

  switch(PduR_GetQueueTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)))){
#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      PduR_RmIf_SingleBufferHandling(rmDestIdx, rmGDest, &destPduInfo);
      break;
#endif
#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      PduR_RmIf_FifoHandling(rmDestIdx, rmGDest, &destPduInfo);
      break;
#endif
    default:

      break;
  }

  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestIdx);
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_RoutePdu(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;

  {
    PduR_RmDestRomIterType rmDestIdx;

#if(PDUR_SMDATAPLANEROM == STD_ON)

    if(PduR_IsSmSrcRomUsedOfRmSrcRom(rmSrcIdx)){
      PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx = PduR_GetSmSrcRomIdxOfRmSrcRom(rmSrcIdx);
      PduR_GetSmSrcFilterFctPtr(PduR_GetSmSrcFilterFctPtrIdxOfSmSrcRom(smSrcRomIdx)) (smSrcRomIdx, info);
    }
#endif

    for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++){
#if(PDUR_RPGROM == STD_ON)

      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))
#endif
      {
#if(PDUR_SMDATAPLANEROM == STD_ON)
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
        PduR_FilterReturnType filterResult = PDUR_FILTER_PASS;

        if(PduR_IsSmGDestRomUsedOfRmGDestRom(rmGDestRomIdx))
        {
          PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx = PduR_GetSmGDestRomIdxOfRmGDestRom(rmGDestRomIdx);
          filterResult = PduR_GetSmGDestFilterFctPtr(PduR_GetSmGDestFilterFctPtrIdxOfSmGDestRom(smGDestRomIdx)) (smGDestRomIdx, info);
        }
        if(filterResult == PDUR_FILTER_PASS)
#endif
        {
#if(PDUR_MCQBUFFERROM == STD_ON)
          PduR_CoreManagerRomIdxOfMmRomType destCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)));
          PduR_CoreManagerRomIdxOfMmRomType srcCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestIdx)));

          if((srcCoreIdx != destCoreIdx)
#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
             && (PduR_GetRoutingTypeOfRmDestRom(rmDestIdx) != PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM)
#endif
            )
          {
            if(PduR_McQ_WriteData(PduR_GetMcQBufferRomIdxOfSrcCoreRom(PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(destCoreIdx) + srcCoreIdx), (PduR_RmDestRomEndIdxOfRmSrcRomType) rmDestIdx, info) == E_OK)
            {
              retVal &= E_OK;
            }
            else
            {
              PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, PDUR_E_MCQ_QUEUE_OVERFLOW);
              retVal &= E_NOT_OK;
            }
          }

          else
#endif
          {
            retVal &= PduR_RmIf_DispatchIfDestPdu((PduR_RmDestRomEndIdxOfRmSrcRomType) rmDestIdx, info);
          }
        }
      }

    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(info);
  PDUR_DUMMY_STATEMENT(retVal);

  return retVal;
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_DispatchIfDestPdu(PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;

  PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

  switch(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx)){
#if(PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM:
      PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);
      retVal = E_OK;
      break;
#endif
#if(PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
      retVal = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, info, !PduR_IsRmDestRomUsedOfRmGDestRom(rmGDestRomIdx));
      break;
#endif
#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM:
      retVal = PduR_RmIf_ProcessNoBufferedGwRouting(rmDestRomIdx, info);
      break;
#endif
#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM:
      retVal = PduR_RmIf_ProcessBufferedRouting(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx), rmDestRomIdx, rmGDestRomIdx, info);
      break;
#endif
    default:

      break;
  }

  return retVal;
}
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessNoBufferedGwRouting(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(info == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
#endif
  {
    PduR_RmIf_RxIndicationNoBuffer(rmDestIdx, info);
    retVal = E_OK;
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, errorId);
  }
#endif
  PDUR_DUMMY_STATEMENT(errorId);

  return retVal;
}
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessBufferedRouting(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx, PduR_RmGDestRomIterType rmGDestRomIdx
   ,                                                                             P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(info == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
#endif
  {
#if(PDUR_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM == STD_ON)
    if((PduR_GetPduLengthHandlingStrategyOfRmDestRom(rmDestIdx) == PDUR_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM)
       || (info->SduLength <= PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))))
#endif
    {
#if(PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON)
      if(PduR_IsTriggerTransmitSupportedOfRmSrcRom(rmSrcIdx))
      {
        uint8 sduData[PDUR_MAX_TRIGGER_TRANSMIT_PDU_SIZE] = { 0u };
        PduInfoType pduInfo;
        pduInfo.SduDataPtr = sduData;
        pduInfo.SduLength = PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

        retVal &= PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), &pduInfo);
        PduR_RmIf_Forward2Buffer(rmDestIdx, &pduInfo);
      }
      else
#endif
      {
        PduR_RmIf_Forward2Buffer(rmDestIdx, info);
        retVal &= E_OK;
      }

#if((PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && (PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON))
      if(PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx) == PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM)
      {
        if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcIdx))
        {
          PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx));
        }
      }
#endif
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, errorId);
  }
#endif
  PDUR_DUMMY_STATEMENT(errorId);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);

  return retVal;
}
#endif

#if(PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_TriggerTransmit(PduR_RmDestRomIterType rmDestIdx, CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = PDUR_E_NO_ERROR;

#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(info == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
#endif
  {
    PduR_Lock_LockRoutingPathByDestPdu(rmDestIdx);
    {
      PduR_RmGDestRomIterType rmGDestIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
      PduInfoType queuedPduInfo;
      PduR_RmDestRomIterType rmDestRomIdx;

      if(PduR_QAL_Get(rmGDestIdx, &rmDestRomIdx, &queuedPduInfo) == E_OK)
      {
        if(info->SduLength >= queuedPduInfo.SduLength)
        {
          info->SduLength = queuedPduInfo.SduLength;
          PduR_Core_MemCpyRamToRam(info->SduDataPtr, queuedPduInfo.SduDataPtr, queuedPduInfo.SduLength);
          retVal = E_OK;
        }
      }
    }
    PduR_Lock_UnlockRoutingPathByDestPdu(rmDestIdx);
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_RMIF_TXTT, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
  return retVal;
}
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx){
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    PduR_GetFctPtrOfRmIf_TxConfirmation_StateHandler(PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) ((PduR_RmGDestRomIterType) rmGDestRomIdx);
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
}
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation_StateHandler_RM_TX_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduInfoType destPduInfo;
  PduR_RmDestRomIterType rmDestRomIdx;

  PduR_QAL_Remove(rmGDestRomIdx);

  if(PduR_QAL_Get(rmGDestRomIdx, &rmDestRomIdx, &destPduInfo) == E_OK){
    if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE)){
      PduR_QAL_Flush(rmGDestRomIdx);
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
      PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_PDU_INSTANCES_LOST);
    }
  }
  else{
    PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
  }
}
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation_StateHandler_RM_TX_IDLE(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_QAL_Flush(rmGDestRomIdx);
  PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
#endif
  PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_PDU_INSTANCES_LOST);
}
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_RmIf_TruncateDlc(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  PduLengthType dataLengthcopy = info->SduLength;

  if(info->SduLength > PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest))){
    dataLengthcopy = PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest));
  }
  PDUR_DUMMY_STATEMENT(rmGDest);
  return dataLengthcopy;
}
#endif

#if((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr){
  return PduR_GetPutFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, rmDestRomIdx, pduLength, sduDataPtr);
}
#endif

#if((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  return PduR_GetGetFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, rmDestRomIdx, info);
}
#endif

#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Remove(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_GetRemoveFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx);
}
#endif

#if((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_DEFERREDEVENTCACHEROM == STD_ON))

LOCAL_INLINE FUNC(uint16, PDUR_CODE) PduR_QAL_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx){
  return PduR_GetGetFillLevelFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx);
}
#endif

#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Flush(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_GetFlushFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx);
}
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_RmIf_MainFunction(PduR_RmGDestRomIterType rmGDestRomIdx){
  if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx)
      && (PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx)) == PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM)){
    PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
    {
      switch(PduR_GetDirectionOfRmGDestRom(rmGDestRomIdx))
      {
#if(PDUR_EXISTS_TX_DIRECTIONOFRMGDESTROM == STD_ON)

        case PDUR_TX_DIRECTIONOFRMGDESTROM:
        {
          PduInfoType destPduInfo;
          PduR_RmDestRomIterType rmDestRomIdx;

          if(PduR_QAL_Get(rmGDestRomIdx, &rmDestRomIdx, &destPduInfo) == E_OK)
          {
            Std_ReturnType retValTramsmit = E_NOT_OK;

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
            if(PduR_GetQueueTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx)) == PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM)
            {
              retValTramsmit = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, FALSE);
              PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
              if(retValTramsmit != E_OK)
              {
                PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, PDUR_E_PDU_INSTANCES_LOST);
                PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
              }
            }
#endif
#if((PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
            else
#endif
#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
            {
              retValTramsmit = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE);

              if(retValTramsmit == E_OK)
              {
                PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
              }
              else
              {
                PduR_QAL_Flush(rmGDestRomIdx);
                PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, PDUR_E_PDU_INSTANCES_LOST);
                PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
              }
            }
#endif
          }
          break;
        }
#endif
#if((PDUR_EXISTS_RX_DIRECTIONOFRMGDESTROM == STD_ON) && (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))

        case PDUR_RX_DIRECTIONOFRMGDESTROM:
        {
          PduInfoType destPduInfo;
          PduR_RmDestRomIterType rmDestRomIdx;

          while(PduR_QAL_Get(rmGDestRomIdx, &rmDestRomIdx, &destPduInfo) == E_OK)
          {
            PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &destPduInfo);
            PduR_QAL_Remove(rmGDestRomIdx);
          }
          break;
        }
#endif
        default:

          break;
      }
    }
    PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
  }
}
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_RmIf_DisableRoutingAction(PduR_RmDestRomIterType rmDestRomIdx){
  PduR_RmGDestRomIterType rmGDestIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

  switch(PduR_GetQueueTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestIdx))){
#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      {
        PDUR_DUMMY_STATEMENT(rmGDestIdx);
      }
      break;
#endif
#if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      PduR_QAL_Flush(rmGDestIdx);
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);
      break;
#endif
    default:

      break;
  }

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_Rm_MultipleSourceHandler_Reset(rmGDestIdx);
#endif
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

