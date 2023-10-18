#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Mc.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
FUNC(Std_ReturnType, PDUR_CODE) PduR_MF_UpToLo(
      P2CONST(PduR_MT_UpToLo,               AUTOMATIC, PDUR_CONST  ) upToLoTable
   ,      VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) mcId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
){
   PduR_GT_TpPtr gt;
   P2CONST(PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST) fifo;
   PduR_TpSessDynPtr SessionPtr;
   PduR_TpConnDynPtr ConnectionPtr;
   P2CONST(PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) tablePtr = upToLoTable;
   VAR(Std_ReturnType, AUTOMATIC) rtn = E_NOT_OK;
   VAR(Std_ReturnType, AUTOMATIC) result = E_NOT_OK;
   if(upToLoTable != NULL_PTR){
      while(tablePtr->upId < mcId){
         tablePtr++;
      }
      while(tablePtr->upId == mcId){
         rtn = PduR_loTransmitTable[tablePtr->upToLo.loTransmitID].PduR_loTransmitFunc(
            tablePtr->upToLo.loId,
            info);
         if(rtn == E_OK){
            if((tablePtr->isTpModule) && (tablePtr->upSrcLayerName == PDUR_NULL_BSWMODNAME)){
               gt = PDUR_GW_TP_BASE;
               while(gt->loId != mcId){
                  gt++;
               }
               fifo = (gt->buffer);
               ConnectionPtr = fifo->connectionTable;
               SessionPtr = ConnectionPtr->primarySession;
               SessionPtr->Tx_E_OK_Count++;
            }
            result = E_OK;
         }
         tablePtr++;
      }
   }
   return result;
}

FUNC(Std_ReturnType, PDUR_CODE) PduR_MF_CancelTransmit_UpToLo(
      P2CONST(PduR_MT_UpToLo,            AUTOMATIC, PDUR_CONST) upToLoTable
   ,      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC            ) mcId
){
   P2CONST(PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) tablePtr = upToLoTable;
   VAR(Std_ReturnType,     AUTOMATIC            ) rtn = E_NOT_OK;
   VAR(uint8,              AUTOMATIC            ) cnt_Not_Ok = 0;
   if(upToLoTable != NULL_PTR){
      while(tablePtr->upId < mcId){
         tablePtr++;
      }
      while(tablePtr->upId == mcId){
         rtn = PduR_loCancelTransmitTable[tablePtr->upToLo.loCancelTransmitID].PduR_loCancelTransmitFunc(
            tablePtr->upToLo.loId);
         if(rtn != E_OK){
            cnt_Not_Ok++;
         }
         tablePtr++;
      }
      if(cnt_Not_Ok > 0){
         rtn = E_NOT_OK;
      }
   }
   return rtn;
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

