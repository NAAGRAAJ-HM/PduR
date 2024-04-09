#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(uint16, PDUR_CODE) PduR_GetConfigurationId(void){
   return PduR_iGetConfigurationId();
}

FUNC(uint16, PDUR_CODE) PduR_iGetConfigurationId(void){ //TBD: delete
   return PDUR_CONFIGURATION_ID;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

