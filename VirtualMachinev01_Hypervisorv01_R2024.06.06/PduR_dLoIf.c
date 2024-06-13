#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Cfg.hpp"
#include "PduR_LoIf.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
){
   PduR_rCanIfTxConfirmation( id );
}

FUNC(void, PDUR_CODE) PduR_CanIfRxIndication(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr
){
   PduR_rCanIfRxIndication((id), (ptr));
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

