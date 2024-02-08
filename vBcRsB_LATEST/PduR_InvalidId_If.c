#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(Std_ReturnType, PDUR_CODE) PduR_invId_IfTriggerTransmit(
        VAR(Type_SwcServiceCom_tIdPdu,                  AUTOMATIC) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) data
){ //TBD: Move to different c file
   (void)id;
   (void)data;
   return E_NOT_OK;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

