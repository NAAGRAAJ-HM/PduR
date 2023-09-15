

#define PDUR_FM_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Bm.hpp"
#include "PduR_Fm.hpp"
#include "PduR_RmTp.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_FMFIFORAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_ReleaseFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_Init(void){
  {
    PduR_FmFifoRamIterType fmFifoRamIdx;
    for(fmFifoRamIdx = 0u; fmFifoRamIdx < PduR_GetSizeOfFmFifoRam(); fmFifoRamIdx++){
#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
      PduR_SetTpTxSmStateOfFmFifoRam(fmFifoRamIdx, PDUR_RM_TX_IDLE_TPTXSMSTATEOFFMFIFORAM);
#endif
      PduR_SetPendingConfirmationsOfFmFifoRam(fmFifoRamIdx, 0u);
      PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx));
      PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx));
      PduR_SetFillLevelOfFmFifoRam(fmFifoRamIdx, 0u);
    }
  }
  {
    PduR_FmFifoElementRamIterType fmFifoElementRamIdx;
    for(fmFifoElementRamIdx = 0u; fmFifoElementRamIdx < PduR_GetSizeOfFmFifoElementRam(); fmFifoElementRamIdx++){
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);
      PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM);
      PduR_SetDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx, FALSE);
      PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);
    }
  }
  {
    PduR_FmFifoInstanceRamIterType fmFifoInstanceRamIdx;
    for(fmFifoInstanceRamIdx = 0u; fmFifoInstanceRamIdx < PduR_GetSizeOfFmFifoInstanceRam(); fmFifoInstanceRamIdx++){
      PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(fmFifoInstanceRamIdx, PDUR_NO_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM);
    }
  }
}
#endif

#if(PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_Fm_InitDedicatedIfTxBuffer(void){
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0u; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++){
    if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx)){
      PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      if(!PduR_IsSingleBufferRomUsedOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx))
#endif
      {
        if(PduR_IsDedicatedTxBufferOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx))
        {
          if(PduR_IsFmFifoInstanceRomUsedOfRmGDestRom(rmGDestRomIdx))
          {
            PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
            PduR_FmFifoElementRamIterType possilbeFmFifoElementRamIdx;
            for(possilbeFmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); possilbeFmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx);
                possilbeFmFifoElementRamIdx++)
            {
              PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx = 0u;
              if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK)
              {
                PduLengthType bufferSizePtr = 0u;
                PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0u;
                if(PduR_Bm_AllocateTxBuffer(fmFifoRomIdx, fmFifoElementRamIdx, 0u, 0u, &bufferSizePtr, &allocatedTxBufferIdxPtr, FALSE) == BUFREQ_OK)
                {
                  PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
                  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);
                  PduR_SetDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx, TRUE);
                }
                else
                {
                  PduR_Det_ReportError(PDUR_RMIF_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
                }
              }
              else
              {
                PduR_Det_ReportError(PDUR_RMIF_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
              }
            }
          }
          else
          {
            PduR_Det_ReportError(PDUR_RMIF_INIT_DEDICATEDTXBUFFER, PDUR_E_FATAL);
          }
        }
      }
    }
  }
}
#endif

#if((PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM  == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_FreeFifoElement(PduR_FmFifoRomIterType fmFifoRomIdx, PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx){
  if(PduR_GetFillLevelOfFmFifoRam(fmFifoRomIdx) > 0u){
    PduR_DecFillLevelOfFmFifoRam(fmFifoRomIdx);
    PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRomIdx, fmFifoElementRamWriteIdx);

    if(!PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamWriteIdx)){
      PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);
    }
    else{
      PduR_Det_ReportError(PDUR_FM_FREEFIFOELEMENT, PDUR_E_FATAL);
    }
  }
  else{
    PduR_Det_ReportError(PDUR_FM_FREEFIFOELEMENT, PDUR_E_FATAL);
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext(PduR_FmFifoRamIterType fmFifoRamIdx){
  PduR_FmFifoElementRamIterType peekedfmFifoElementRamTPReadIdx;
  if(PduR_Fm_Peek(fmFifoRamIdx, &peekedfmFifoElementRamTPReadIdx) == E_OK){
    PduR_GetFctPtrOfFm_ActivateNext_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(peekedfmFifoElementRamTPReadIdx)) (peekedfmFifoElementRamTPReadIdx, E_OK);
  }
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmSmStateHandler_FM_WRITE_FINISHED_READ_PENDING(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfRmTp_FinishReception_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRamIdx)) (rmSrcIdx, result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  PduR_FmFifoRamIterType fmFifoRamIdx = PduR_GetFmFifoRomIdxOfRmBufferedTpPropertiesRom(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfRmTp_CheckReady2Transmit_TpTxSmStateHandler(PduR_GetTpTxSmStateOfFmFifoRam(fmFifoRamIdx)) (rmSrcIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  PduR_Det_ReportError(PDUR_FM_ACTIVATENEXT, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_FM_WRITE_FINISHED_READ_PENDING(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_FINISHED_READ_ACTIVE_STATEOFFMFIFOELEMENTRAM);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_READ_ACTIVE_STATEOFFMFIFOELEMENTRAM);
}
#endif
#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  PduR_Det_ReportError(PDUR_FMACTIVATEREAD, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_FM_READ_FINISHED(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  PduR_Bm_ResetTxBuffer(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
  PduR_Fm_ReleaseFifoElement(fmFifoElementRamWriteIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif
#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_FM_WRITE_READ_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_FINISHED_READ_ACTIVE_STATEOFFMFIFOELEMENTRAM);
  PDUR_DUMMY_STATEMENT(result);
}
#endif
#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result){
  if(result == E_OK){
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_FINISHED_READ_PENDING_STATEOFFMFIFOELEMENTRAM);
  }
  else{
    PduR_Bm_ResetTxBuffer(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx));
    PduR_Fm_ReleaseFifoElement(fmFifoElementRamWriteIdx);
  }
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_FM_WRITE_FINISHED_READ_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result){
  PduR_Bm_ResetTxBuffer(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
  PduR_Fm_ReleaseFifoElement(fmFifoElementRamReadIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_FM_WRITE_READ_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result){
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamReadIdx, PDUR_FM_READ_FINISHED_STATEOFFMFIFOELEMENTRAM);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result){
  PduR_Det_ReportError(PDUR_FMFINISHREAD, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamReadIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result){
  PDUR_DUMMY_STATEMENT(fmFifoElementRamReadIdx);
  PDUR_DUMMY_STATEMENT(result);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateWrite_FmSmStateHandler_FM_ALLOCATED_WITH_BUFFER(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_WRITE_ACTIVE_STATEOFFMFIFOELEMENTRAM);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateWrite_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  PduR_Det_ReportError(PDUR_FM_ACTIVATEWRITE, PDUR_E_FATAL);
  PDUR_DUMMY_STATEMENT(fmFifoElementRamWriteIdx);
}
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_NoAction(PduR_RmGDestRomIterType rmGDestRomIdx){
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);
}
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_FM_WRITE_FINISHED_READ_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmTp_CancelTransmitPreparation(fmFifoElementRamReadIdx);
}
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
  PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfRmTp_CancelReceive_TpRxSmStateHandler(tpRxSmState) (rmSrcIdx);
}
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_FM_WRITE_READ_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);
  PduR_RmSrcRomIterType rmSrcIdx = PduR_GetRmSrcRomIdxOfRmDestRom(PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx));
  PduR_TpRxSmStateOfRmBufferedTpPropertiesRamType tpRxSmState = PduR_GetTpRxSmStateOfRmBufferedTpPropertiesRam(PduR_GetRmBufferedTpPropertiesRomIdxOfRmSrcRom(rmSrcIdx));
  PduR_GetFctPtrOfRmTp_CancelReceive_TpRxSmStateHandler(tpRxSmState) (rmSrcIdx);
  PduR_RmTp_CancelTransmitPreparation(fmFifoElementRamReadIdx);
}
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_Peek(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx){
  Std_ReturnType retVal = E_NOT_OK;

  while(PduR_GetFillLevelOfFmFifoRam(fmFifoRamIdx) > 0u){
    PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_Fm_IncrementReadIndex(fmFifoRamIdx);

    if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamReadIdx) == E_OK){
      *fmFifoElementRamIdx = fmFifoElementRamReadIdx;
      retVal = E_OK;
      break;
    }
  }
  return retVal;
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AssignFifoElement(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamWriteIdxOfFmFifoRamType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx){
  Std_ReturnType retVal = E_NOT_OK;

  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx);

  if(PduR_Fm_AllocateFifoElement(fmFifoElementRamWriteIdx) == E_OK){
    *fmFifoElementRamIdx = fmFifoElementRamWriteIdx;

    if(fmFifoElementRamWriteIdx >= (PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx) - 1u)){
      fmFifoElementRamWriteIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx);
    }
    else{
      fmFifoElementRamWriteIdx++;
    }

    PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamWriteIdx);
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AllocateFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx){
  Std_ReturnType retVal = E_NOT_OK;
  if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamWriteIdx) != E_OK){
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_ALLOCATED_STATEOFFMFIFOELEMENTRAM);
    retVal = E_OK;
  }
  return retVal;
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_IsFifoElementAllocated(PduR_FmFifoElementRamIterType fmFifoElementRamIdx){
  Std_ReturnType retVal = E_OK;

  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx)){
    if((PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx) == (PduR_BmTxBufferInstanceRomIterType) PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM)){
      retVal = E_NOT_OK;
    }
  }
  else{
    if((PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx) == (PduR_BmTxBufferInstanceRomIterType) PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM)){
      retVal = E_NOT_OK;
    }
  }
  return retVal;
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_AssignTxBuffer2FifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx){
  PduR_SetStateOfFmFifoElementRam(fmFifoElementRamWriteIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);
  PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx, bmTxBufferRomIdx);
}
#endif

#if(PDUR_FMFIFORAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Fm_ReleaseFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamIdx){
  PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_RMDESTROMIDXOFFMFIFOELEMENTRAM);

  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamIdx)){
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_ALLOCATED_WITH_BUFFER_STATEOFFMFIFOELEMENTRAM);
  }
  else{
    PduR_SetStateOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_FM_IDLE_STATEOFFMFIFOELEMENTRAM);

    PduR_SetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM);
  }
}
#endif

#if((PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(PduR_FmFifoElementRamIterType, PDUR_CODE) PduR_Fm_IncrementReadIndex(PduR_FmFifoRamIterType fmFifoRamIdx){
  PduR_FmFifoElementRamReadIdxOfFmFifoRamType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx);

  if(fmFifoElementRamReadIdx >= ((PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRamIdx) - 1u))){
    fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRamIdx);
  }
  else{
    fmFifoElementRamReadIdx++;
  }
  PduR_DecFillLevelOfFmFifoRam(fmFifoRamIdx);
  PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRamIdx, fmFifoElementRamReadIdx);

  return fmFifoElementRamReadIdx;
}
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_PutFifo(PduR_RmGDestRomIterType rmGDest, PduR_RmDestRomIterType rmDest, PduLengthType pduLength, SduDataPtrType sduDataPtr){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDest));
  PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamIdx;

  if(PduR_Fm_AssignFifoElement(fmFifoRomIdx, &fmFifoElementRamIdx) == E_OK){
    PduLengthType bufferSizePtr = 0u;
    PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType allocatedTxBufferIdxPtr = 0u;

    PduR_IncFillLevelOfFmFifoRam(fmFifoRomIdx);
    if(PduR_Bm_AllocateTxBuffer(fmFifoRomIdx, fmFifoElementRamIdx, pduLength, 0u, &bufferSizePtr, &allocatedTxBufferIdxPtr, FALSE) == BUFREQ_OK){
      PduR_Fm_AssignTxBuffer2FifoElement(fmFifoElementRamIdx, allocatedTxBufferIdxPtr);
      PduR_SetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamIdx, (PduR_RmDestRomIdxOfFmFifoElementRamType) rmDest);

      PduR_GetFctPtrOfFm_ActivateWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx);
      (void) PduR_Bm_PutData(PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx), pduLength, sduDataPtr);
      PduR_GetFctPtrOfFm_FinishWrite_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamIdx)) (fmFifoElementRamIdx, E_OK);

      retVal = E_OK;
    }
    else{
      PduR_Fm_FreeFifoElement(fmFifoRomIdx, fmFifoElementRamIdx);
    }
  }
  return retVal;
}
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_FmFifoRamIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx);

  PduR_GetFctPtrOfFm_FinishRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx, E_OK);
  PduR_Bm_ResetTxBufferInstance(PduR_GetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx)));
  (void) PduR_Fm_IncrementReadIndex(fmFifoRomIdx);
}
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;

  PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx = PduR_GetFmFifoElementRamReadIdxOfFmFifoRam(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx)));

  if(PduR_Fm_IsFifoElementAllocated(fmFifoElementRamReadIdx) == E_OK){
    PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx);
    PduR_BmTxBufferInstanceRomStartIdxOfBmTxBufferRomType bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx);

    PduR_Bm_AssignAssociatedBuffer2DestinationInstance(bmTxBufferRomIdx, bmTxBufferInstanceRomIdx);
    PduR_SetBmTxBufferInstanceRomIdxOfFmFifoInstanceRam(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx), bmTxBufferInstanceRomIdx);

    *rmDestRomIdx = PduR_GetRmDestRomIdxOfFmFifoElementRam(fmFifoElementRamReadIdx);

    PduR_GetFctPtrOfFm_ActivateRead_FmSmStateHandler(PduR_GetStateOfFmFifoElementRam(fmFifoElementRamReadIdx)) (fmFifoElementRamReadIdx);
    PduR_Bm_CopyDataAsPtr(bmTxBufferInstanceRomIdx, info, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx));
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(uint16, PDUR_CODE) PduR_Fm_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx){
  return PduR_GetFillLevelOfFmFifoRam(PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx)));
}
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFo(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_FmFifoRomIterType fmFifoRomIdx = PduR_GetFmFifoRomIdxOfFmFifoInstanceRom(PduR_GetFmFifoInstanceRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_FmFifoElementRamIterType fmFifoElementRamIdx;

  for(fmFifoElementRamIdx = PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx); fmFifoElementRamIdx < PduR_GetFmFifoElementRamEndIdxOfFmFifoRom(fmFifoRomIdx); fmFifoElementRamIdx++){
    PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamIdx);

    if(bmTxBufferRomIdx != PDUR_NO_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM){
      PduR_Bm_ResetTxBuffer(bmTxBufferRomIdx);
      PduR_Bm_ResetTxBufferInstance(PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(bmTxBufferRomIdx));
    }
    PduR_Fm_ReleaseFifoElement(fmFifoElementRamIdx);
  }
  PduR_SetFillLevelOfFmFifoRam(fmFifoRomIdx, 0u);
  PduR_SetFmFifoElementRamReadIdxOfFmFifoRam(fmFifoRomIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx));
  PduR_SetFmFifoElementRamWriteIdxOfFmFifoRam(fmFifoRomIdx, PduR_GetFmFifoElementRamStartIdxOfFmFifoRom(fmFifoRomIdx));
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

