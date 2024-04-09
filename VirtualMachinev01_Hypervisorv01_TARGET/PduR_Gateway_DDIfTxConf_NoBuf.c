#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Gw.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(void, PDUR_CODE) PduR_GF_DDIf_NoBuf_TxConfirmation_Func(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId
){
    (void)gwayId;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

