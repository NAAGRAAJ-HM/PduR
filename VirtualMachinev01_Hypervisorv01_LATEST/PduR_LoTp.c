#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Cfg.hpp"
#include "PduR_LoTp.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(void, PDUR_CODE) infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Rx(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  VAR(Std_ReturnType,            AUTOMATIC) std
){
   PduR_rCanTpRxIndication(
         (id)
      ,  (std)
   );
}

FUNC(void, PDUR_CODE) infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Tx(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  VAR(Std_ReturnType,            AUTOMATIC) std
){
   PduR_rCanTpTxConfirmation(
         (id)
      ,  (std)
   );
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
){
   return(
      PduR_rCanTpCopyRxData(
            (id)
         ,  (info)
         ,  (bufferSizePtr)
      )
   );
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,      VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC              ) TpSduLength
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
){
   return(
      PduR_rCanTpStartOfReception(
            (id)
         ,  (info)
         ,  (TpSduLength)
         ,  (bufferSizePtr)
      )
   );
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC)               id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(RetryInfoType,                 TYPEDEF, PDUR_APPL_DATA) retry
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) availableDataPtr
){
   return(
      PduR_rCanTpCopyTxData(
            (id)
         ,  (info)
         ,  (retry)
         ,  (availableDataPtr)
      )
   );
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

