#ifndef PDUR_CANIF_H
#define PDUR_CANIF_H

#include "PduR.hpp"
#include "EcuabCanIf.hpp"

extern FUNC(void, PDUR_CODE) PduR_CanIfRxIndication(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr
);

extern FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
);

#endif
