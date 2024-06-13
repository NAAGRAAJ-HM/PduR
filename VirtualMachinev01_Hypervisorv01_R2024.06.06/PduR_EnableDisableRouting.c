#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(void, PDUR_CODE) PduR_DisableRouting(
      VAR(PduR_RoutingPathGroupIdType, AUTOMATIC) id
   ,  VAR(boolean,                     AUTOMATIC) initialize
){
   (void)id;
   (void)initialize;
}

FUNC(void, PDUR_CODE) PduR_EnableRouting(
   VAR(PduR_RoutingPathGroupIdType, AUTOMATIC) id
){
   (void)id;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

