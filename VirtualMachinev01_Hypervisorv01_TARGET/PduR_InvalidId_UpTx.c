#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_UpTransmit(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr
){
   (void)id;
   (void)ptr;
    return E_NOT_OK;
}

FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_UpCancelTransmit(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
){
   (void)id;
   return E_NOT_OK;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

