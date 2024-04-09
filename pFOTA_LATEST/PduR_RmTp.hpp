#if !defined (PDUR_RMTP_H)
#define PDUR_RMTP_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "Types_SwcServicePduR.hpp"
#include "CfgSwcServicePduR.hpp"
#include "SwcServicePduR_Lcfg.hpp"

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_Init(void);
#endif

#if(PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDTPPROPERTIESROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_Init_DedicatedTxBuffer(void);
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CopyTxData(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                             P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif

#if((PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
FUNC(void, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_TpTxConfirmation(PduR_RmGDestRomIdxOfTxTp2SrcType rmGDestRomIdx, Std_ReturnType result);
#endif

#if((PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx);
#endif

#if(PDUR_HASTPTXBUFFEREDFORWARDINGOFGENERALPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_UpStartOfReception(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception(PduR_RmSrcRomIterType rmSrcIdx
   ,                                                             P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                             PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                       P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_CancelTransmitPreparation(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication(PduR_RmSrcRomIdxOfRxTp2DestType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_Transmit_MultiDest(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_IDLE(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_CheckReady2Transmit_TpTxSmStateHandler_NoAction(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_IDLE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_TRANSMISSION_FINISHED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishReception_TpTxSmStateHandler_NoAction(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_FINISHED_TRANSMISSION_ACTIVE(PduR_RmDestRomIterType rmGDestRomIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_RM_TX_RECEPTION_TRANSMISSION_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_FinishTransmission_TpTxSmStateHandler_FatalError(PduR_RmDestRomIterType rmGDestRomIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_RM_RX_IDLE(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                                           PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_StartOfReception_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                                                               PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength
   ,                                                                                       SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength
   ,                                                                                        SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_CopyRxData_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, PduLengthType pduLength
   ,                                                                                         SduDataPtrType sduDataPtr, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_UnexpectedCall(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_TpRxIndication_TpRxSmStateHandler_RM_RX_ACTIVE_OR_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ACTIVE(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_FatalError(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmTp_CancelReceive_TpRxSmStateHandler_RM_RX_ABORTED(PduR_RmSrcRomIterType rmSrcIdx);
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
#endif

