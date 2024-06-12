#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Cfg.hpp"
#include "PduR_UpTp.hpp"
#include "PduR_Dcm.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr
){
    return (PduR_rDcmTransmit( (id) , (ptr)));
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

