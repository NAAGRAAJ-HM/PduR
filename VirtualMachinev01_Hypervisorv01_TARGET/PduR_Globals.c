#include "Std_Types.hpp"

#include "PduR_Prv.hpp"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.hpp"
P2CONST(PduR_PBConfigType, PDUR_VAR, PDUR_APPL_CONST) PduR_Base;
    VAR(PduR_StateType,    PDUR_VAR                 ) PduR_State;
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.hpp"

