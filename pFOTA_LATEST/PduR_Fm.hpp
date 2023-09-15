

#if !defined (PDUR_FM_H)
#define PDUR_FM_H

#include "Types_SwcServicePduR.hpp"
#include "CfgSwcServicePduR.hpp"
#include "SwcServicePduR_Lcfg.hpp"

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_Init(void);
#endif

#if(PDUR_DEDICATEDTXBUFFEROFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_InitDedicatedIfTxBuffer(void);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_Peek(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamIterType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx);
#endif

#if((PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_FreeFifoElement(PduR_FmFifoRomIterType fmFifoRomIdx, PduR_FmFifoElementRamWriteIdxOfFmFifoRamType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_IsFifoElementAllocated(PduR_FmFifoElementRamIterType fmFifoElementRamIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AllocateFifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_NoAction(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_FM_WRITE_READ_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_FM_WRITE_FINISHED_READ_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(void, PDUR_CODE) PduR_Fm_TpDisableRouting_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmSmStateHandler_FM_WRITE_FINISHED_READ_PENDING(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_AssignTxBuffer2FifoElement(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, PduR_BmTxBufferRomIdxOfFmFifoElementRamType bmTxBufferRomIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateRead_FmSmStateHandler_FM_WRITE_FINISHED_READ_PENDING(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_FM_READ_FINISHED(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_FM_WRITE_READ_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishWrite_FmSmStateHandler_FM_WRITE_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_FM_WRITE_FINISHED_READ_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_FM_WRITE_READ_ACTIVE(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FinishRead_FmSmStateHandler_NoAction(PduR_FmFifoElementRamIterType fmFifoElementRamReadIdx, Std_ReturnType result);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateWrite_FmSmStateHandler_FM_ALLOCATED_WITH_BUFFER(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateWrite_FmSmStateHandler_FatalError(PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx);
#endif

#if(PDUR_FMFIFORAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_AssignFifoElement(PduR_FmFifoRamIterType fmFifoRamIdx, P2VAR(PduR_FmFifoElementRamWriteIdxOfFmFifoRamType, AUTOMATIC, PDUR_APPL_DATA) fmFifoElementRamIdx);
#endif

#if(PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_ActivateNext(PduR_FmFifoRamIterType fmFifoRamIdx);
#endif

#if((PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))

FUNC(PduR_FmFifoElementRamIterType, PDUR_CODE) PduR_Fm_IncrementReadIndex(PduR_FmFifoRamIterType fmFifoRamIdx);
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_PutFifo(PduR_RmGDestRomIterType rmGDest, PduR_RmDestRomIterType rmDest, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_Fm_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(uint16, PDUR_CODE) PduR_Fm_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Fm_FlushFiFo(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"
#endif

