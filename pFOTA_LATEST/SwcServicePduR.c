#define PDUR_SOURCE
#ifdef __cplusplus
extern "C"
{
#endif

#include "SwcServicePduR.hpp"
#include "PduR_Bm.hpp"
#include "PduR_Fm.hpp"
#include "PduR_IFQ.hpp"
#include "PduR_Sm.hpp"
#include "PduR_RmIf.hpp"
#include "PduR_RmTp.hpp"
#include "PduR_RmTp_TxInst.hpp"
#include "PduR_McQ.hpp"
#include "PduR_Lock.hpp"
#include "SchM_PduR.hpp"

#if(PDUR_MULTICORE == STD_ON)
#include "SwcServiceOs.hpp"
#endif

#if((PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST == STD_ON) || (PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST == STD_ON) || (PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST == STD_ON) || (PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO == STD_ON) || (PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP == STD_ON) || (PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC == STD_ON))
#include "BswM_PduR.hpp"
#endif

#if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
#include "EcuM_Error.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_RPGROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_RmDestRpgRom(void);
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Init(void);
#endif

#if((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CancelTransmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)))

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DispatchMainfuntion(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_Init(void);
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_ReadFlush(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx);
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_EvC_IsFull(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx);
#endif

#if(PDUR_VERSION_INFO_API == STD_ON)

FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versionInfo){
  uint8 errorId = PDUR_E_NO_ERROR;
#if(PDUR_DEV_ERROR_DETECT == STD_ON)

  if(versionInfo == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
#endif
  {
    versionInfo->vendorID = (uint16) PDUR_VENDOR_ID;
    versionInfo->moduleID = (uint8) PDUR_MODULE_ID;
    versionInfo->sw_major_version = (uint8) PDUR_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = (uint8) PDUR_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = (uint8) PDUR_SW_PATCH_VERSION;
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_VERSIONINFO, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
}
#endif

FUNC(PduR_PBConfigIdType, PDUR_CODE) PduR_GetConfigurationId(void){
  uint16 configID = 0u;

  uint8 errorId = PDUR_E_NO_ERROR;
  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
  else{
    configID = PduR_GetConfigId();
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_CONFIGURATIONID, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
  return configID;
}

#if(PDUR_TX2LO == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfTx2Lo())
#if(PDUR_INVALIDHNDOFTX2LO == STD_ON)
          || (PduR_IsInvalidHndOfTx2Lo(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
#if(PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO == STD_ON)
    if(PduR_IsBswMPduRTransmitCallbackOfTx2Lo(id)){
      BswM_PduR_Transmit(id, info);
    }
#endif
    {
      {
        retVal = PduR_GetRmTransmitFctPtr(PduR_GetRmTransmitFctPtrIdxOfTx2Lo(id)) (PduR_GetRmSrcRomIdxOfTx2Lo(id), info);
      }
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_TX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(info);

  return retVal;
}
#endif

#if(PDUR_RXIF2DEST == STD_ON)

FUNC(void, PDUR_CODE) PduR_LoIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((RxPduId >= PduR_GetSizeOfRxIf2Dest())
#if(PDUR_INVALIDHNDOFRXIF2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxIf2Dest(RxPduId))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
#if(PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST == STD_ON)
    if(PduR_IsBswMPduRRxIndicationCallbackOfRxIf2Dest(RxPduId)){
      BswM_PduR_RxIndication(RxPduId, info);
    }
#endif
    {
      (void) PduR_RmIf_RoutePdu(PduR_GetRmSrcRomIdxOfRxIf2Dest(RxPduId), info);
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_IFRXIND, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(RxPduId);
  PDUR_DUMMY_STATEMENT(info);
}
#endif

#if(PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)

FUNC(void, PDUR_CODE) PduR_LoIfTxConfirmation(PduIdType TxPduId){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((TxPduId >= PduR_GetSizeOfTxIf2Up())
#if(PDUR_INVALIDHNDOFTXIF2UP == STD_ON)
          || (PduR_IsInvalidHndOfTxIf2Up(TxPduId))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
#if(PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP == STD_ON)
    if(PduR_IsBswMPduRTxConfirmationCallbackOfTxIf2Up(TxPduId)){
      BswM_PduR_TxConfirmation(TxPduId);
    }
#endif
#if(PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
    if(PduR_IsTxConfirmationUsedOfTxIf2Up(TxPduId)){
      PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_GetRmGDestRomIdxOfTxIf2Up(TxPduId));
    }
#endif
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_IFTXCFM, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(TxPduId);
}
#endif

#if((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_LoIfTriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((TxPduId >= PduR_GetSizeOfTxIf2Up())
#if(PDUR_INVALIDHNDOFTXIF2UP == STD_ON)
          || (PduR_IsInvalidHndOfTxIf2Up(TxPduId))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
    retVal = PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_GetRmGDestRomIdxOfTxIf2Up(TxPduId), info);
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_TT, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(TxPduId);
  PDUR_DUMMY_STATEMENT(info);

  return retVal;
}
#endif

#if(PDUR_RXTP2DEST == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength
   ,                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  uint8 errorId = PDUR_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#if(PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
    PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);

#if((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
    PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdxOfApiFwdDest = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);
    boolean apiFwdDestWasCalled = FALSE;
#endif

#if(PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST == STD_ON)
    if(PduR_IsBswMPduRTpStartOfReceptionCallbackOfRxTp2Dest(id)){
      BswM_PduR_TpStartOfReception(id, info, TpSduLength, bufferSizePtr);
    }
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    {
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      for(; rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcRomIdx); rmDestRomIdx++)
      {
        if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM)
        {
#endif
#if(PDUR_RPGROM == STD_ON)
          if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
#endif
          {
            PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpStartOfReceptionFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info, TpSduLength, bufferSizePtr);
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            rmDestRomIdxOfApiFwdDest= rmDestRomIdx;
            apiFwdDestWasCalled = TRUE;
            break;
#endif
          }
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        }
      }
#endif
    }
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx)){
#if(PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if(apiFwdDestWasCalled == TRUE)
      {
          if(retVal == BUFREQ_OK)
          {
            PduLengthType bufferSizeOfQueuedDestinations;

            retVal = PduR_RmTp_StartOfReception(rmSrcRomIdx, info, TpSduLength, &bufferSizeOfQueuedDestinations);
            if(retVal == BUFREQ_OK)
            {
              if(bufferSizeOfQueuedDestinations < *bufferSizePtr)
              {
                *bufferSizePtr = bufferSizeOfQueuedDestinations;
              }
            }
            else
            {
              PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdxOfApiFwdDest);
              PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), E_NOT_OK);
            }
          }
      }
      else
#endif
      {
        retVal = PduR_RmTp_StartOfReception(rmSrcRomIdx, info, TpSduLength, bufferSizePtr);
      }
    }
#endif
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_SOR, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(info);
  PDUR_DUMMY_STATEMENT(TpSduLength);
  PDUR_DUMMY_STATEMENT(bufferSizePtr);

  return retVal;
}
#endif
#if(PDUR_RXTP2DEST == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr){
  uint8 errorId = PDUR_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#if(PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
    PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);
#if((PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
    boolean apiFwdDestWasCalled = FALSE;
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    {
      PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      for(; rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcRomIdx); rmDestRomIdx++)
      {
        if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM)
        {
#endif
#if(PDUR_RPGROM == STD_ON)
          if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
#endif
          {
            PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
            retVal = PduR_GetUpTpCopyRxDataFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info, bufferSizePtr);
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            apiFwdDestWasCalled = TRUE;
            break;
#endif
          }
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        }
      }
#endif
    }
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

    if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx)){
#if(PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if(apiFwdDestWasCalled == TRUE)
      {
        if(retVal == BUFREQ_OK)
        {
          PduLengthType bufferSizeOfQueuedDestinations;

          retVal = PduR_RmTp_CopyRxData(rmSrcRomIdx, info, &bufferSizeOfQueuedDestinations);
          if(retVal == BUFREQ_OK)
          {
            if(bufferSizeOfQueuedDestinations < *bufferSizePtr)
            {
              *bufferSizePtr = bufferSizeOfQueuedDestinations;
            }
          }
        }
      }
      else
#endif
      {
        retVal = PduR_RmTp_CopyRxData(rmSrcRomIdx, info, bufferSizePtr);
      }
    }
#endif
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_CPYRX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(info);
  PDUR_DUMMY_STATEMENT(bufferSizePtr);

  return retVal;
}
#endif
#if(PDUR_TXTP2SRC == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry
   ,                                                      P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr){
  uint8 errorId = PDUR_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfTxTp2Src())
#if(PDUR_INVALIDHNDOFTXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfTxTp2Src(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
    retVal = PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_GetRmGDestRomIdxOfTxTp2Src(id), info, retry, availableDataPtr);
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_CPYTX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(info);
  PDUR_DUMMY_STATEMENT(retry);
  PDUR_DUMMY_STATEMENT(availableDataPtr);

  return retVal;
}
#endif
#if(PDUR_RXTP2DEST == STD_ON)

FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType id, Std_ReturnType result){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfRxTp2Dest())
#if(PDUR_INVALIDHNDOFRXTP2DEST == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Dest(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
#if(PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST == STD_ON)
    if(PduR_IsBswMPduRTpRxIndicationCallbackOfRxTp2Dest(id)){
      BswM_PduR_TpRxIndication(id, result);
    }
#endif

    {
      PduR_RmSrcRomIdxOfRxTp2DestType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRxTp2Dest(id);

#if(PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
      {
        PduR_RmDestRomStartIdxOfRmSrcRomType rmDestRomIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcRomIdx);

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        for(; rmDestRomIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcRomIdx); rmDestRomIdx++)
        {
          if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM)
#endif
          {
            PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);
            PduR_GetUpTpTpRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), result);
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            break;
#endif
          }
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
        }
#endif
      }
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      if(PduR_IsRmBufferedTpPropertiesRomUsedOfRmSrcRom(rmSrcRomIdx))
      {
        PduR_RmTp_TpRxIndication(rmSrcRomIdx, result);
      }
#endif
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_TPRXIND, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(result);
}
#endif
#if(PDUR_TXTP2SRC == STD_ON)

FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType id, Std_ReturnType result){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfTxTp2Src())
#if(PDUR_INVALIDHNDOFTXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfTxTp2Src(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
#if(PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC == STD_ON)
    if(PduR_IsBswMPduRTpTxConfirmationCallbackOfTxTp2Src(id)){
      BswM_PduR_TpTxConfirmation(id, result);
    }
#endif
    PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_GetRmGDestRomIdxOfTxTp2Src(id), result);
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_TPTXCFM, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_CANCELRECEIVESUPPORTEDOFMMROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType id){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfRxTp2Src())
#if(PDUR_INVALIDHNDOFRXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Src(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
    PduR_RmDestRomIdxOfRxTp2SrcType rmDestRomIdx = PduR_GetRmDestRomIdxOfRxTp2Src(id);
    PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
    PduR_MmRomIdxOfRmSrcRomType mmRomIdx = PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx);

    if(PduR_IsCancelReceiveSupportedOfMmRom(mmRomIdx)){
#if(PDUR_RPGROM == STD_ON)
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestRomIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestRomIdx))))
#endif
      {
        PduR_SrcHndOfRmSrcRomType srcHnd = PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx);
        retVal = PduR_GetLoTpCancelReceiveFctPtrOfMmRom(mmRomIdx) (srcHnd);
      }
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_CRX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);

  return retVal;
}
#endif
#if(PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if((id >= PduR_GetSizeOfRxTp2Src())
#if(PDUR_INVALIDHNDOFRXTP2SRC == STD_ON)
          || (PduR_IsInvalidHndOfRxTp2Src(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
  else{
    PduR_RmDestRomIdxOfRxTp2SrcType rmDestRomIdx = PduR_GetRmDestRomIdxOfRxTp2Src(id);
    PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);
    PduR_MmRomIdxOfRmSrcRomType mmRomIdx = PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx);

    if(PduR_IsChangeParameterSupportedOfMmRom(mmRomIdx)){
      PduR_SrcHndOfRmSrcRomType srcHnd = PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx);
      retVal = PduR_GetLoTpChangeParameterFctPtrOfMmRom(mmRomIdx) (srcHnd, parameter, value);
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_CHPARA, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);
  PDUR_DUMMY_STATEMENT(parameter);
  PDUR_DUMMY_STATEMENT(value);

  return retVal;
}
#endif

#if((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))

FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelTransmit(PduIdType id){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_INVALID_REQUEST;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
#if(PDUR_TX2LO == STD_ON)
  else if((id >= PduR_GetSizeOfTx2Lo())
#if(PDUR_INVALIDHNDOFTX2LO == STD_ON)
          || (PduR_IsInvalidHndOfTx2Lo(id))
#endif
    ){
    errorId = PDUR_E_PDU_ID_INVALID;
  }
#endif
#endif
  else{
#if(PDUR_CANCELTRANSMITUSEDOFTX2LO  == STD_ON)
    if(PduR_IsCancelTransmitUsedOfTx2Lo(id)){
      retVal = PduR_Rm_CancelTransmit_MultiDest(PduR_GetRmSrcRomIdxOfTx2Lo(id));
    }
#endif
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_CTX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif

  PDUR_DUMMY_STATEMENT(id);

  return retVal;
}
#endif

#if((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_CancelTransmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx){
  Std_ReturnType retVal = E_NOT_OK;

  PduR_RmDestRomIterType rmDestIdx;

  for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++){
#if(PDUR_RPGROM == STD_ON)
    if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))
#endif
    {
      switch(PduR_GetRoutingTypeOfRmDestRom(rmDestIdx))
      {
#if((PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
        case PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          if(PduR_IsIfCancelTransmitSupportedOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))
          {
            retVal &= PduR_RmIf_MultipleSourceHandler_CancelTransmit(rmDestIdx);
          }
          break;
#endif
#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) && (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
        case PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
          if(PduR_IsTpCancelTransmitSupportedOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))
          {
            retVal &= PduR_RmTp_MultipleSourceHandler_CancelTransmit(rmDestIdx);
          }
          break;
#endif
        default:

          break;
      }
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);

  return retVal;
}
#endif

FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_PBCFG) ConfigPtr){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == TRUE){
    errorId = PDUR_E_ALREADY_INITIALIZED;
  }
  else{
#if(PDUR_USE_INIT_POINTER == STD_ON)
    PduR_ConfigDataPtr = ConfigPtr;
    if(PduR_ConfigDataPtr == NULL_PTR){
#if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
      EcuM_BswErrorHook(PDUR_MODULE_ID, ECUM_BSWERROR_NULLPTR);
#endif
      errorId = PDUR_E_NULL_POINTER;
    }
#if(PDUR_FINALMAGICNUMBER == STD_ON)
    else if(PduR_GetFinalMagicNumber() != PDUR_FINAL_MAGIC_NUMBER){
#if(PDUR_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
      EcuM_BswErrorHook(PDUR_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#endif
      errorId = PDUR_E_INIT_FAILED;
      PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
    }
    else{
    }
#endif
#else
    if(ConfigPtr != NULL_PTR){
      errorId = PDUR_E_INIT_FAILED;
    }
#endif
    if(errorId == PDUR_E_NO_ERROR){
#if(PDUR_RPGROM == STD_ON)
      PduR_Init_RmDestRpgRom();
#endif
#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
      PduR_Rm_MultipleSourceHandler_Init();
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)
      PduR_Bm_Init();
#endif

#if(PDUR_FMFIFORAM == STD_ON)
      PduR_Fm_Init();
#endif

#if(PDUR_SMDATAPLANEROM == STD_ON)
      PduR_Sm_Init();
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_RmIf_InitDestPduState();
#endif
#if(PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      PduR_Fm_InitDedicatedIfTxBuffer();
#endif
#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      PduR_RmIf_SingleBuffer_Init();
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_RmTp_Init();
#endif

#if(PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM == STD_ON)
      PduR_RmTp_Init_DedicatedTxBuffer();
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)
      PduR_McQ_Init();
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
      PduR_EvC_Init();
#endif

#if(PDUR_SPINLOCKRAM == STD_ON)
      PduR_Lock_Init();
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
      PduR_IFQ_Init();
#endif

      PduR_SetInitialized(TRUE);
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_INIT, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
}

#if(PDUR_MAIN_FUNCTION == STD_ON)

FUNC(void, PDUR_CODE) PduR_MainFunction(void){
#if(PDUR_MULTICORE == STD_ON)
  uint8 errorId = PDUR_E_NO_ERROR;
#endif

  if(PduR_IsInitialized()){
#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
    boolean processAllDestinations;
#endif
    PduR_CoreManagerRomIterType coreManagerRomIdx = 0;
#if(PDUR_MULTICORE == STD_ON)
    PduR_CoreId2CoreManagerRomIterType coreId = (PduR_CoreId2CoreManagerRomIterType) GetCoreID();
    coreManagerRomIdx = PduR_GetCoreManagerRomIdxOfCoreId2CoreManagerRom(coreId);
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
    if(coreId >= PduR_GetSizeOfCoreId2CoreManagerRom()){
      errorId = PDUR_E_INVALID_CORE_ID;
    }else
#if(PDUR_INVALIDHNDOFCOREID2COREMANAGERROM == STD_ON)
    if(PduR_IsInvalidHndOfCoreId2CoreManagerRom(coreId)){
      errorId = PDUR_E_INVALID_CORE_ID;
    }else
#endif
#endif
#endif
    {
#if((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
      {
        PduR_SrcCoreRomEndIdxOfCoreManagerRomType srcCoreRomIdx;
        boolean anyEventQueueHasOverflown = FALSE;

        for(srcCoreRomIdx = PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx < PduR_GetSrcCoreRomEndIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx++)
        {
          boolean isEvCFull = PduR_EvC_IsFull(PduR_GetDeferredEventCacheRomIdxOfSrcCoreRom(srcCoreRomIdx));
          anyEventQueueHasOverflown = anyEventQueueHasOverflown | isEvCFull;
        }
        processAllDestinations = anyEventQueueHasOverflown;

        if(processAllDestinations == TRUE)
        {
          for(srcCoreRomIdx = PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx < PduR_GetSrcCoreRomEndIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx++)
          {
            PduR_EvC_ReadFlush(PduR_GetDeferredEventCacheRomIdxOfSrcCoreRom(srcCoreRomIdx));
          }
        }

        else
        {
          for(srcCoreRomIdx = PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx < PduR_GetSrcCoreRomEndIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx++)
          {
            PduR_RmGDestRomIterType rmGDestRomIdx;
            PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheRomIdx = PduR_GetDeferredEventCacheRomIdxOfSrcCoreRom(srcCoreRomIdx);
            PduR_DeferredEventCacheArrayRamLengthOfDeferredEventCacheRomType readLimit = PduR_GetDeferredEventCacheArrayRamLengthOfDeferredEventCacheRom(deferredEventCacheRomIdx);

            while(PduR_EvC_Get(deferredEventCacheRomIdx, &rmGDestRomIdx) == E_OK)
            {
              PduR_DispatchMainfuntion(rmGDestRomIdx);
              readLimit--;
              if(readLimit == 0u)
              {
                break;
              }
            }
          }
        }
      }
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
      if(processAllDestinations == TRUE)
#endif
      {
        PduR_MmRomIndIterType mmIndIdx;
        for(mmIndIdx = PduR_GetMmRomIndStartIdxOfCoreManagerRom(coreManagerRomIdx); mmIndIdx < PduR_GetMmRomIndEndIdxOfCoreManagerRom(coreManagerRomIdx); mmIndIdx++)
        {
          PduR_MmRomIterType mmIdx = PduR_GetMmRomInd(mmIndIdx);

          PduR_RmGDestRomIterType rmGDestRomIdx;
          for(rmGDestRomIdx = PduR_GetRmGDestRomStartIdxOfMmRom(mmIdx); rmGDestRomIdx < PduR_GetRmGDestRomEndIdxOfMmRom(mmIdx); rmGDestRomIdx++)
          {
            PduR_DispatchMainfuntion(rmGDestRomIdx);
          }
        }
      }
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

      PduR_McQ_MainFunction((PduR_CoreManagerRomIdxOfMmRomType) coreManagerRomIdx);
#endif
    }
  }

#if(PDUR_MULTICORE == STD_ON)

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
#endif
}
#endif

#if(PDUR_RPGROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Init_RmDestRpgRom(void){
  {
    PduR_RmDestRpgRomIterType rmDestRpgRomIdx;
    for(rmDestRpgRomIdx = 0u; rmDestRpgRomIdx < PduR_GetSizeOfRmDestRpgRom(); rmDestRpgRomIdx++){
      PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, PduR_GetInitialEnabledCntOfRmDestRpgRom(rmDestRpgRomIdx));
    }
  }
  {
    PduR_RpgRamIterType rpgIdx;
    for(rpgIdx = 0u; rpgIdx < PduR_GetSizeOfRpgRam(); rpgIdx++){
      PduR_SetEnabledOfRpgRam(rpgIdx, PduR_IsEnabledAtInitOfRpgRom(rpgIdx));
    }
  }
}
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Init(void){
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0u; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++){
    PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
  }
}
#endif

FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_GetSrcDestPdu(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx){
  Std_ReturnType retVal = E_OK;

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx)){
    PduR_RmDestRomIterType localRmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestNto1InfoRam(PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx));
    if(localRmDestRomIdx != PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM){
      *rmDestRomIdx = localRmDestRomIdx;
    }
    else{
      retVal = E_NOT_OK;
    }
  }
  else
#endif
  {
    *rmDestRomIdx = PduR_GetRmDestRomIdxOfRmGDestRom(rmGDestRomIdx);
  }

  return retVal;
}

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Reset(PduR_RmGDestRomIterType rmGDestRomIdx){
  if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx)){
    PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

    PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, FALSE);
    PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, PDUR_NO_RMDESTROMIDXOFRMGDESTNTO1INFORAM);
  }
}
#endif

FUNC(void, PDUR_CODE) PduR_InitMemory(void){
  PduR_SetInitialized(FALSE);
#if(PDUR_USE_INIT_POINTER == STD_ON)
  PduR_ConfigDataPtr = (P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG)) NULL_PTR;
#endif
}

#if(PDUR_RPGROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_UNINIT;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if(id >= PduR_GetSizeOfRpgRom()){
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#if(PDUR_INVALIDHNDOFRPGROM == STD_ON)
  else if(PduR_IsInvalidHndOfRpgRom(id)){
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#endif
#endif
  else{
    if(!PduR_IsEnabledOfRpgRam(id)){
      PduR_RmDestRpgRomIndIterType rmDestRpgRomIndIdx;
      for(rmDestRpgRomIndIdx = PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(id); rmDestRpgRomIndIdx < PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(id); rmDestRpgRomIndIdx++)
      {
        PduR_RmDestRpgRomIndType rmDestRpgRomIdx = PduR_GetRmDestRpgRomInd(rmDestRpgRomIndIdx);
        PduR_RmDestRomIterType rmDestRomIdx = PduR_GetRmDestRomIdxOfRmDestRpgRom(rmDestRpgRomIdx);
        PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
        {
          PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx, PduR_GetEnabledCntOfRmDestRpgRam(rmDestRpgRomIdx) + 1u);
        }
        PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
      }
      PduR_SetEnabledOfRpgRam(id, TRUE);
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_ENABLEROUTING, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
}
#endif

#if(PDUR_RPGROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id){
  uint8 errorId = PDUR_E_NO_ERROR;

  if(PduR_IsInitialized() == FALSE){
    errorId = PDUR_E_UNINIT;
  }
#if(PDUR_DEV_ERROR_DETECT == STD_ON)
  else if(id >= PduR_GetSizeOfRpgRom()){
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#if(PDUR_INVALIDHNDOFRPGROM == STD_ON)
  else if(PduR_IsInvalidHndOfRpgRom(id)){
    errorId = PDUR_E_ROUTING_PATH_GROUP_ID_INVALID;
  }
#endif
#endif
  else{
    if(PduR_IsEnabledOfRpgRam(id)){
      PduR_RmDestRpgRomIndIterType rmDestRpgRomIndIdx;
      for(rmDestRpgRomIndIdx = PduR_GetRmDestRpgRomIndStartIdxOfRpgRom(id); rmDestRpgRomIndIdx < PduR_GetRmDestRpgRomIndEndIdxOfRpgRom(id); rmDestRpgRomIndIdx++)
      {
        PduR_RmDestRpgRomIndType rmDestRpgRomInd = PduR_GetRmDestRpgRomInd(rmDestRpgRomIndIdx);
        PduR_RmDestRomIterType rmDestRomIdx = PduR_GetRmDestRomIdxOfRmDestRpgRom(rmDestRpgRomInd);
        PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
        {
#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          if(PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
          {
            PduR_RmIf_DisableRoutingAction(rmDestRomIdx);
          }
#endif
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
          if(PDUR_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
          {
            PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfRmDestRpgRom(rmDestRpgRomInd));
            PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
            PduR_FmFifoElementRamIterType fmFifoElementRamTPReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
            PduR_StateOfFmFifoElementRamType fifoSmState = PduR_GetStateOfFmFifoElementRam(fmFifoElementRamTPReadIdx);

            PduR_GetFctPtrOfFm_TpDisableRouting_FmSmStateHandler(fifoSmState) (rmGDestRomIdx);
          }
#endif
          PduR_SetEnabledCntOfRmDestRpgRam(rmDestRpgRomInd, (PduR_GetEnabledCntOfRmDestRpgRam(rmDestRpgRomInd) - 1u));
        }
        PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
      }
      PduR_SetEnabledOfRpgRam(id, FALSE);
    }
  }

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_DISABLEROUTING, errorId);
  }
#else
  PDUR_DUMMY_STATEMENT(errorId);
#endif
}
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && ((PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)))

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_DispatchMainfuntion(PduR_RmGDestRomIterType rmGDestRomIdx){
#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
  if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx)){
    PduR_RmIf_MainFunction(rmGDestRomIdx);
  }
#endif
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
  if(PduR_IsRmGDestTpTxStateRamUsedOfRmGDestRom(rmGDestRomIdx)){
    PduR_RmTp_TxInst_MainFunction(rmGDestRomIdx);
  }
#endif
}
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_Init(void){
  PduR_DeferredEventCacheRomIterType deferredEventCacheRomIdx;
  for(deferredEventCacheRomIdx = 0u; deferredEventCacheRomIdx < PduR_GetSizeOfDeferredEventCacheRom(); deferredEventCacheRomIdx++){
    PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheRomIdx);

    PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheRomIdx, startIdxOfBuffer);
    PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheRomIdx, startIdxOfBuffer);
  }
}
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_EvC_Put(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx, PduR_RmGDestRomIterType rmGDestRomIdx){
  Std_ReturnType retVal = E_NOT_OK;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  {
    PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_GetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx);
    PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_GetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx);

    if(writeIdx < PduR_GetSizeOfDeferredEventCacheArrayRam()){
      PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx);
      PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx) - 1u;

      if(PduR_EvC_IsFull(deferredEventCacheIdx) == TRUE)
      {
        retVal = E_NOT_OK;
      }

      else if(writeIdx < readIdx)
      {
        PduR_SetRmGDestRomIdxOfDeferredEventCacheArrayRam(writeIdx, (PduR_RmGDestRomIdxOfDeferredEventCacheArrayRamType) rmGDestRomIdx);
        PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, writeIdx + 1u);
        retVal = E_OK;
      }

      else
      {
        PduR_SetRmGDestRomIdxOfDeferredEventCacheArrayRam(writeIdx, (PduR_RmGDestRomIdxOfDeferredEventCacheArrayRamType) rmGDestRomIdx);

        if(writeIdx == endIdxOfBuffer)
        {
          PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, startIdxOfBuffer);
        }
        else
        {
          PduR_SetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx, writeIdx + 1u);
        }
        retVal = E_OK;
      }
    }
    else{
      PduR_Det_ReportError(PDUR_EVC_PUT, PDUR_E_FATAL);
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  return retVal;
}
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_EvC_WriteDeferredEventCache(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest){
  PduR_CoreManagerRomIdxOfMmRomType srcCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDest)));
  PduR_CoreManagerRomIdxOfMmRomType destCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDest));

  (void) PduR_EvC_Put(PduR_GetDeferredEventCacheRomIdxOfSrcCoreRom(PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(destCoreIdx) + srcCoreIdx), rmGDest);
}
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_EvC_Get(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx, P2VAR(PduR_RmGDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmGDestRomIdxPtr){
  Std_ReturnType retVal;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  {
    PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_GetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx);
    PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_GetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx);

    if(readIdx == writeIdx){
      retVal = E_NOT_OK;
    }

    else{
      PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx);
      PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx) - 1u;

      *rmGDestRomIdxPtr = PduR_GetRmGDestRomIdxOfDeferredEventCacheArrayRam(readIdx);

      if(readIdx == endIdxOfBuffer)
      {
        PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, startIdxOfBuffer);
      }
      else
      {
        PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, readIdx + 1u);
      }

      retVal = E_OK;
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  return retVal;
}
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_EvC_ReadFlush(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx){
  PduR_SetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx, PduR_GetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx));
}
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)

LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_EvC_IsFull(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx){
  boolean retVal;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
  {
    PduR_DeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRamType readIdx = PduR_GetDeferredEventCacheArrayRamReadIdxOfDeferredEventCacheRam(deferredEventCacheIdx);
    PduR_DeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRamType writeIdx = PduR_GetDeferredEventCacheArrayRamWriteIdxOfDeferredEventCacheRam(deferredEventCacheIdx);

    PduR_DeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRomType startIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamStartIdxOfDeferredEventCacheRom(deferredEventCacheIdx);
    PduR_DeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRomType endIdxOfBuffer = PduR_GetDeferredEventCacheArrayRamEndIdxOfDeferredEventCacheRom(deferredEventCacheIdx) - 1u;

    if(((writeIdx + 1u) == readIdx) || ((readIdx == startIdxOfBuffer) && (writeIdx == endIdxOfBuffer))){
      retVal = TRUE;
    }
    else{
      retVal = FALSE;
    }
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();

  return retVal;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
