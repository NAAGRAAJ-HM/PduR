

#if !defined (PDUR_RMTP_TXINST_H)
#define PDUR_RMTP_TXINST_H

#include "Types_SwcServicePduR.hpp"
#include "CfgSwcServicePduR.hpp"
#include "SwcServicePduR_Lcfg.hpp"

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_RmTxinstIdle(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_RmTxinstWaiting(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_TriggerTransmit_FatalError(PduR_RmDestRomIterType rmDestRomIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info
   ,                                                              P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxinstActive(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength
   ,                                                                             SduDataPtrType sduDataPtr
   ,                                                                             P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC
   ,                                                                                                                                            PDUR_APPL_DATA) availableDataPtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength
   ,                                                                             SduDataPtrType sduDataPtr
   ,                                                                             P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC
   ,                                                                                                                                            PDUR_APPL_DATA) availableDataPtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CopyTxData_RmTxinstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, PduLengthType pduLength
   ,                                                                              SduDataPtrType sduDataPtr
   ,                                                                              P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC
   ,                                                                                                                                             PDUR_APPL_DATA) availableDataPtr);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_RmTxinstActiveOrRmTxinstAborted(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_TxConfirmation_UnexpectedCall(PduR_RmGDestRomIterType rmGDestRomIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit(PduR_RmDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_RmTxinstWaiting(PduR_RmDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_RmTxinstActive(PduR_RmDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_RmTxinstAborted(PduR_RmDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_RmTp_TxInst_CancelTransmit_FatalError(PduR_RmDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_RmTp_TxInst_MainFunction(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"
#endif

