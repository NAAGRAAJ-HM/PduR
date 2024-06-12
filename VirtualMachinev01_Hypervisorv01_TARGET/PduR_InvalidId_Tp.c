#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_invId_TpCopyRxData(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
){
   (void)id;
   (void)info;
   (void)bufferSizePtr;
   return BUFREQ_E_NOT_OK;
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_invId_TpStartOfReception(
        VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,    VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC              ) TpSduLength
   ,  P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
){
   (void)id;
   (void)TpSduLength;
   (void)bufferSizePtr;
   return BUFREQ_E_NOT_OK;
}

FUNC(void, PDUR_CODE) PduR_invId_TpRxIndication(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  VAR(Std_ReturnType,            AUTOMATIC) result
){
   (void)id;
   (void)result;
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_invId_TpCopyTxData(
          VAR(Type_SwcServiceCom_tIdPdu,                   AUTOMATIC) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(RetryInfoType,                 TYPEDEF, PDUR_APPL_DATA) retry
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) availableDataPtr
){
   info = info;
   (void)id;
   (void)info;
   (void)retry;
   (void)availableDataPtr;
   return BUFREQ_E_NOT_OK;
}

FUNC(void, PDUR_CODE) PduR_invId_TpTxConfirmation(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  VAR(Std_ReturnType,            AUTOMATIC) result
){
   (void)id;
   (void)result;
}

FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_UpCancelReceive(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
){
   (void)id;
   return E_NOT_OK;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

