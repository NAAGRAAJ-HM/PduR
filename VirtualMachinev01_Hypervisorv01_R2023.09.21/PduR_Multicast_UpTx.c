#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Mc.hpp"
#include "PduR_Gw.hpp"
#include "PduR_Dcm.hpp"
#include "PduR_Dcm_Up.hpp"
#include "PduR_Com.hpp"
#include "PduR_Com_Up.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(Std_ReturnType, PDUR_CODE) PduR_MF_Com_Transmit_Func(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
){
   return PduR_MF_UpToLo(PDUR_COM_MC_TX_BASE, id, info);
}

FUNC(Std_ReturnType, PDUR_CODE) PduR_GwMcTx_Transmit_Func(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
){
   return PduR_MF_UpToLo(PDUR_GW_MC_TX_BASE, id, info);
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

