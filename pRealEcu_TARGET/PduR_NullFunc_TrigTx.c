#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(Std_ReturnType, PDUR_CODE) PduR_NF_TriggerTransmit_Func(
        VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC                ) id
   ,  P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, PDUR_APPL_DATA) data
){
   (void)id;
   (void)data;
   return E_NOT_OK;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

