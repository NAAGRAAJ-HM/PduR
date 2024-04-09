#ifndef PDUR_CANTP_H
#define PDUR_CANTP_H

#include "PduR.hpp"
#include "CanTp.hpp"

extern FUNC(void, PDUR_CODE) infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Rx( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     VAR(Std_ReturnType, AUTOMATIC) std );

extern FUNC(void, PDUR_CODE) infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Tx( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     VAR(Std_ReturnType, AUTOMATIC) std );

extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpProvideTxBuffer( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     P2VAR(P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA), TYPEDEF, PDUR_APPL_DATA) ptr
   ,     VAR(uint16, AUTOMATIC) len );

extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpProvideRxBuffer( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) len
   ,     P2VAR(P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA), TYPEDEF, PDUR_APPL_DATA) ptr );

extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu,TYPEDEF,PDUR_APPL_DATA) info
   ,     VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
   ,     P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) availableDataPtr );

#endif

