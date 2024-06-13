#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "Dem.hpp"
#include "PduR_Cfg_Internal.hpp"
#include "PduR_Gw.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(void, PDUR_CODE) PduR_Init(
   P2CONST(Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr
){
   PduR_iInit(ConfigPtr);
}

FUNC(void, PDUR_CODE) PduR_iInit(
   P2CONST(Type_CfgSwcServicePduR_st, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr
){
   if(PduR_State == PDUR_UNINIT){
      PduR_State = PDUR_REDUCED;
      (void)ConfigPtr;
      PduR_Base = &PduR_GlobalPBConfig;
      PduR_State = PDUR_ONLINE;
   }
}

FUNC(void, PDUR_CODE) PduR_iInit_multicast(
   P2VAR(PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state
){
   state->pduPtr     = NULL_PTR;
   state->allocError = BUFREQ_OK;
   state->txFailure  = E_OK;
   state->txConf     = 0;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

