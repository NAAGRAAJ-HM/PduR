

#define PDUR_BM_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Bm.hpp"
#include "PduR_Lock.hpp"

#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))
#define PduR_Core_MemCpyRomToRam(d, s, l)    VStdMemCpyRomToRam((d), (s), (l))

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBuffer(void);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBufferInstance(void);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_After_PutData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_EndIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                       CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_EndIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                            PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_ReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_ReadIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                             PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                  PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_StateHandler_BUFFER_READ4WRITE(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                         PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMain_After_GetData(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_WriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_WriteIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx,
                                                                                                PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_EndIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                      CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_EndIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_WRITE4READ(PduR_BmTxBufferRomIterType txBufferElementStateIdx,
                                                                                                                PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                       PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(PduR_BmTxBufferRomIterType txBufferElementStateIdx,
                                                                                                                        PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_WriteIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_Instance_WriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_ReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearBufferSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalBufferSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_InstanceReadIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_WriteIdx_And_PutData(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength, SduDataPtrType sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_InstanceWriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_InstanceReadIdx_WrapAround(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                      SduDataPtrType sduDataPtr);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_ReadIdx_And_UpdateMainReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMainReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_AssignAssociatedBufferInstance2DestinationInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferRomIterType bmTxBufferRomIdx);
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBuffer(void){
  PduR_BmTxBufferRomIterType txBufferStateIdx;
  for(txBufferStateIdx = 0u; txBufferStateIdx < PduR_GetSizeOfBmTxBufferRam(); txBufferStateIdx++){
    PduR_Bm_ResetTxBuffer(txBufferStateIdx);
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Init_TxBufferInstance(void){
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;
  for(bmTxBufferInstanceRomIdx = 0u; bmTxBufferInstanceRomIdx < PduR_GetSizeOfBmTxBufferInstanceRam(); bmTxBufferInstanceRomIdx++){
    PduR_Bm_ResetTxBufferInstance(bmTxBufferInstanceRomIdx);
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  BufReq_ReturnType retVal = BUFREQ_OK;

  if(PduR_Bm_GetLinearBufferSize(txBufferElementStateIdx) > pduLength){
    PduR_Bm_Put_Between_WriteIdx_EndIdx(txBufferElementStateIdx, pduLength, sduDataPtr);
    if(pduLength != 0u){
      PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM);
    }
  }
  else if(PduR_Bm_GetLinearBufferSize(txBufferElementStateIdx) == pduLength){
    if(PduR_Bm_GetLinearBufferSize(txBufferElementStateIdx) == PduR_Bm_GetTotalBufferSize(txBufferElementStateIdx)){
      PduR_Bm_Put_Between_WriteIdx_EndIdx(txBufferElementStateIdx, pduLength, sduDataPtr);
      PduR_Bm_Switch_WriteIdx(txBufferElementStateIdx);
      PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM);
    }
    else{
      PduR_Bm_Put_Between_WriteIdx_EndIdx(txBufferElementStateIdx, pduLength, sduDataPtr);
      PduR_Bm_Switch_WriteIdx(txBufferElementStateIdx);
      PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM);
    }
  }
  else if(PduR_Bm_GetTotalBufferSize(txBufferElementStateIdx) > pduLength){
    PduR_Bm_Switch_WriteIdx_And_PutData(txBufferElementStateIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else if(PduR_Bm_GetTotalBufferSize(txBufferElementStateIdx) == pduLength){
    PduR_Bm_Switch_WriteIdx_And_PutData(txBufferElementStateIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else{
    retVal = BUFREQ_E_NOT_OK;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_AssignAssociatedBuffer2DestinationInstance(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  if(bmTxBufferInstanceRomIdx > PduR_GetBmTxBufferInstanceRomEndIdxOfBmTxBufferRom(bmTxBufferRomIdx)){
    PduR_Det_ReportError(PDUR_RMTP_ASSIGNASSOCIATEDBUFFER2DESTINATION, PDUR_E_FATAL);
  }
  else{
    PduR_SetTxBufferUsedOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, TRUE);
    PduR_Bm_AssignAssociatedBufferInstance2DestinationInstance(bmTxBufferInstanceRomIdx, bmTxBufferRomIdx);
    PduR_SetBmTxBufferArrayRamInstanceStopIdxOfBmTxBufferRam(bmTxBufferRomIdx, (((PduR_BmTxBufferArrayRamInstanceStopIdxOfBmTxBufferRamType) bmTxBufferInstanceRomIdx) + 1u));
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_AssignAssociatedBufferInstance2DestinationInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferRomIterType bmTxBufferRomIdx){
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx));
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx));
  PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx));
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_CopyData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  PduR_BmTxBufferRomIterType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx);
  PDUR_DUMMY_STATEMENT(bmTxBufferInstanceRomIdx);

  PduR_Core_MemCpyRamToRam(sduDataPtr, PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx)), pduLength);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = 0u;
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx) - (PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx) -
                                                                             PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx));
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = 0u;
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearBufferSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx)) -
        PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = 0u;
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx)) -
        PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalBufferSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx)) -
        (PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) - PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx));
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = 0u;
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx));
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  BufReq_ReturnType retVal = BUFREQ_OK;
  switch(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      if(pduLength != 0u)
      {
        retVal = BUFREQ_E_BUSY;
      }
      break;
    }
    default:
      break;
  }
  if((retVal == BUFREQ_OK) && (pduLength != 0u)){
    retVal = PduR_Bm_UpdateMainReadIdx(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx));
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMain_After_GetData(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  BufReq_ReturnType retVal = BUFREQ_OK;
  switch(PduR_GetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_WRITE4READ(txBufferElementStateIdx, distanceInstReadIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(txBufferElementStateIdx, distanceInstReadIdx);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(txBufferElementStateIdx, distanceInstReadIdx);
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      PduR_Det_ReportError(PDUR_GW_BUFMGR_UPDATEMAIN_AFTER_GETDATA, PDUR_E_FATAL);
      retVal = BUFREQ_E_BUSY;
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_WriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                        CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + pduLength) > PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx))){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_Core_MemCpyRamToRam(sduDataPtr, PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)), pduLength);
    PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + pduLength);
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_WRITEIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_WriteIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx) + distanceInstReadIdx) > PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx)){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx, (PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx) + distanceInstReadIdx));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_WRITEIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                       PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  BufReq_ReturnType retVal = BUFREQ_OK;

  if(PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx) == pduLength){
    if(PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx) == PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx)){
      PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
      PduR_Bm_Switch_InstanceReadIdx(bmTxBufferInstanceRomIdx);
      PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
    }
    else{
      PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
      PduR_Bm_Switch_InstanceReadIdx(bmTxBufferInstanceRomIdx);
      PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
    }
  }
  else if(PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx) > pduLength){
    PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
  }
  else if(PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx) > pduLength){
    PduR_Bm_InstanceReadIdx_WrapAround(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
  }
  else if(PduR_Bm_GetTotalDataSizeInstance(bmTxBufferInstanceRomIdx) == pduLength){
    PduR_Bm_InstanceReadIdx_WrapAround(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
  }
  else{
    retVal = BUFREQ_E_BUSY;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_FULL_OR_READ4WRITE(PduR_BmTxBufferRomIterType txBufferElementStateIdx,
                                                                                                                        PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  BufReq_ReturnType retVal = BUFREQ_OK;
  if(PduR_Bm_GetLinearDataSize(txBufferElementStateIdx) == distanceInstReadIdx){
    if(PduR_Bm_GetLinearDataSize(txBufferElementStateIdx) == PduR_Bm_GetTotalDataSize(txBufferElementStateIdx)){
      PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_EndIdx(txBufferElementStateIdx, distanceInstReadIdx);
      PduR_Bm_Switch_ReadIdx(txBufferElementStateIdx);
      PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM);
    }
    else{
      PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_EndIdx(txBufferElementStateIdx, distanceInstReadIdx);
      PduR_Bm_Switch_ReadIdx(txBufferElementStateIdx);
      PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM);
    }
  }
  else if(PduR_Bm_GetLinearDataSize(txBufferElementStateIdx) > distanceInstReadIdx){
    PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_EndIdx(txBufferElementStateIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else if(PduR_Bm_GetTotalDataSize(txBufferElementStateIdx) > distanceInstReadIdx){
    PduR_Bm_Switch_ReadIdx_And_UpdateMainReadIdx(txBufferElementStateIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else if(PduR_Bm_GetTotalDataSize(txBufferElementStateIdx) == distanceInstReadIdx){
    PduR_Bm_Switch_ReadIdx_And_UpdateMainReadIdx(txBufferElementStateIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else{
    PduR_Det_ReportError(PDUR_GW_BUFMGR_UPDATEMAIN_AFTER_GETDATA_STATEHANDLER_BUFFER_FULL_OR_READ4WRITE, PDUR_E_FATAL);
    retVal = BUFREQ_E_BUSY;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Get_Between_ReadIdx_EndIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                      CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + pduLength) > (PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx)))){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_Core_MemCpyRamToRam(sduDataPtr, PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)), pduLength);
    PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, (PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + pduLength));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_ENDIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_EndIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx) + distanceInstReadIdx) > PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(txBufferElementStateIdx)){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx, (PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx) + distanceInstReadIdx));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_ENDIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData_StateHandler_BUFFER_WRITE4READ(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  BufReq_ReturnType retVal = BUFREQ_OK;
  if(PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx) == pduLength){
    PduR_Bm_Get_Between_ReadIdx_WriteIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
  }
  else if(PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx) > pduLength){
    PduR_Bm_Get_Between_ReadIdx_WriteIdx(bmTxBufferInstanceRomIdx, pduLength, sduDataPtr);
  }
  else{
    retVal = BUFREQ_E_BUSY;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMain_After_GetData_StateHandler_BUFFER_WRITE4READ(PduR_BmTxBufferRomIterType txBufferElementStateIdx,
                                                                                                                PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  BufReq_ReturnType retVal = BUFREQ_OK;
  if(PduR_Bm_GetLinearDataSize(txBufferElementStateIdx) == distanceInstReadIdx){
    PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_WriteIdx(txBufferElementStateIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else if(PduR_Bm_GetLinearDataSize(txBufferElementStateIdx) > distanceInstReadIdx){
    PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_WriteIdx(txBufferElementStateIdx, distanceInstReadIdx);
  }
  else{
    PduR_Det_ReportError(PDUR_GW_BUFMGR_UPDATEMAIN_AFTER_GETDATA_STATEHANDLER_BUFFER_WRITE4READ, PDUR_E_FATAL);
    retVal = BUFREQ_E_BUSY;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_After_PutData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  switch(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      PduR_Bm_UpdateInstance_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
      break;
    }
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      PduR_Bm_UpdateInstance_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      PduR_Bm_UpdateInstance_StateHandler_BUFFER_READ4WRITE(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      if(distanceInstReadIdx != 0u)
      {
      }
      break;
    }
    default:
      break;
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_ReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx) + pduLength) > PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx)){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_Core_MemCpyRamToRam(PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx)), sduDataPtr, pduLength);
    PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx, (PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx) + pduLength));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_READIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_ReadIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                             PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + distanceInstReadIdx) > PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, (PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + distanceInstReadIdx));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_READIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength,
                                                                                               CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  BufReq_ReturnType retVal = BUFREQ_OK;
  if(PduR_Bm_GetLinearBufferSize(txBufferElementStateIdx) == pduLength){
    PduR_Bm_Put_Between_WriteIdx_ReadIdx(txBufferElementStateIdx, pduLength, sduDataPtr);
    PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else if((PduR_Bm_GetLinearBufferSize(txBufferElementStateIdx) > pduLength)){
    PduR_Bm_Put_Between_WriteIdx_ReadIdx(txBufferElementStateIdx, pduLength, sduDataPtr);

  }
  else{
    retVal = BUFREQ_E_NOT_OK;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_StateHandler_BUFFER_READ4WRITE(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                         PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  if(PduR_Bm_GetLinearBufferSizeInstance(bmTxBufferInstanceRomIdx) == distanceInstReadIdx){
    PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_ReadIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  }
  else if((PduR_Bm_GetLinearBufferSizeInstance(bmTxBufferInstanceRomIdx) > distanceInstReadIdx)){
    PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_ReadIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
  }
  else{
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                                  PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  if(PduR_Bm_GetLinearBufferSizeInstance(bmTxBufferInstanceRomIdx) > distanceInstReadIdx){
    PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_EndIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
    if(distanceInstReadIdx != 0u){
      PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
    }
  }
  else if(PduR_Bm_GetLinearBufferSizeInstance(bmTxBufferInstanceRomIdx) == distanceInstReadIdx){
    if(PduR_Bm_GetLinearBufferSizeInstance(bmTxBufferInstanceRomIdx) == PduR_Bm_GetTotalBufferSizeInstance(bmTxBufferInstanceRomIdx)){
      PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_EndIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
      PduR_Bm_Switch_Instance_WriteIdx(bmTxBufferInstanceRomIdx);
      PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
    }
    else{
      PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_EndIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
      PduR_Bm_Switch_Instance_WriteIdx(bmTxBufferInstanceRomIdx);
      PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
    }
  }
  else if(PduR_Bm_GetTotalBufferSizeInstance(bmTxBufferInstanceRomIdx) > distanceInstReadIdx){
    PduR_Bm_Switch_InstanceWriteIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
  }
  else if(PduR_Bm_GetTotalBufferSizeInstance(bmTxBufferInstanceRomIdx) == distanceInstReadIdx){
    PduR_Bm_Switch_InstanceWriteIdx(bmTxBufferInstanceRomIdx, distanceInstReadIdx);
    PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM);
  }
  else{
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Put_Between_WriteIdx_EndIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  uint8 errorId = PDUR_E_NO_ERROR;

  if((PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx) + pduLength) > (PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(txBufferElementStateIdx))){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_Core_MemCpyRamToRam(PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx)), sduDataPtr, pduLength);
    PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx, (PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx) + pduLength));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_ENDIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_EndIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx,
                                                                                            PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  uint8 errorId = PDUR_E_NO_ERROR;

  PduR_BmTxBufferRomIterType txBufferElementStateIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx);
  if((PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + distanceInstReadIdx) > PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(txBufferElementStateIdx)){
    errorId = PDUR_E_FATAL;
  }
  else{
    PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, (PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) + distanceInstReadIdx));
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_ENDIDX, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);
  PDUR_DUMMY_STATEMENT(txBufferElementStateIdx);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_WriteIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx){
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx));
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_Instance_WriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferRomIterType txBufferElementStateIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx);
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx));

  PDUR_DUMMY_STATEMENT(txBufferElementStateIdx);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_ReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx){
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx));
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_InstanceReadIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferRomIdxOfBmTxBufferInstanceRomType txBufferElementStateIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx);
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx));

  PDUR_DUMMY_STATEMENT(txBufferElementStateIdx);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_WriteIdx_And_PutData(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType pduLength, SduDataPtrType sduDataPtr){
  PduR_BmTxBufferArrayRamIterType pduLengthHead, pduLengthTail;
  pduLengthTail = PduR_Bm_GetLinearBufferSize(txBufferElementStateIdx);
  pduLengthHead = pduLength - pduLengthTail;
  PduR_Bm_Put_Between_WriteIdx_EndIdx(txBufferElementStateIdx, pduLengthTail, sduDataPtr);
  PduR_Bm_Switch_WriteIdx(txBufferElementStateIdx);
  PduR_Bm_Put_Between_WriteIdx_ReadIdx(txBufferElementStateIdx, pduLengthHead, &sduDataPtr[pduLengthTail]);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_InstanceWriteIdx(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  PduR_BmTxBufferArrayRamIterType taillength = PduR_Bm_GetLinearBufferSizeInstance(bmTxBufferInstanceRomIdx);
  PduR_BmTxBufferArrayRamIterType headlenght = distanceInstReadIdx - taillength;
  PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_EndIdx(bmTxBufferInstanceRomIdx, taillength);
  PduR_Bm_Switch_Instance_WriteIdx(bmTxBufferInstanceRomIdx);
  PduR_Bm_UpdateInstance_After_Put_Between_WriteIdx_ReadIdx(bmTxBufferInstanceRomIdx, headlenght);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_Switch_ReadIdx_And_UpdateMainReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx, PduR_BmTxBufferArrayRamIterType distanceInstReadIdx){
  PduR_BmTxBufferArrayRamIterType taillength = PduR_Bm_GetLinearDataSize(txBufferElementStateIdx);
  PduR_BmTxBufferArrayRamIterType headlength = distanceInstReadIdx - taillength;
  PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_EndIdx(txBufferElementStateIdx, taillength);
  PduR_Bm_Switch_ReadIdx(txBufferElementStateIdx);
  PduR_Bm_UpdateMainReadIdx_After_Get_Between_ReadIdx_WriteIdx(txBufferElementStateIdx, headlength);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Bm_InstanceReadIdx_WrapAround(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength, SduDataPtrType sduDataPtr){
  PduR_BmTxBufferArrayRamIterType pduLengthHead, pduLengthTail;
  pduLengthTail = PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx);
  pduLengthHead = pduLength - pduLengthTail;
  PduR_Bm_Get_Between_ReadIdx_EndIdx(bmTxBufferInstanceRomIdx, PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx), sduDataPtr);
  PduR_Bm_Switch_InstanceReadIdx(bmTxBufferInstanceRomIdx);
  PduR_Bm_Get_Between_ReadIdx_WriteIdx(bmTxBufferInstanceRomIdx, pduLengthHead, &sduDataPtr[pduLengthTail]);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

LOCAL_INLINE FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_UpdateMainReadIdx(PduR_BmTxBufferRomIterType txBufferElementStateIdx){
  BufReq_ReturnType retVal = BUFREQ_OK;
  PduR_BmTxBufferArrayRamIterType deltaInstIdxMainIdxTailMainIdx = 0u;
  PduR_BmTxBufferArrayRamIterType deltaInstIdxMainIdxTailInstIdx = 0u;
  boolean bIsAnyInstanceFull = FALSE;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;
  PduR_BmTxBufferArrayRamStartIdxOfBmTxBufferRomType txBufferArrayStartIdx = PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx);
  PduR_BmTxBufferArrayRamIterType txBufferArrayEndIdx = PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(txBufferElementStateIdx);
  PduR_BmTxBufferArrayRamIterType mainReadIdx = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx);
  PduR_BmTxBufferArrayRamIterType currentBeforeDestReadIdx = mainReadIdx;
  PduR_BmTxBufferArrayRamIterType currentAfterDestReadIdx = txBufferArrayEndIdx;
  for(bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(txBufferElementStateIdx);
      bmTxBufferInstanceRomIdx < PduR_GetBmTxBufferArrayRamInstanceStopIdxOfBmTxBufferRam(txBufferElementStateIdx); bmTxBufferInstanceRomIdx++){
    if(PduR_IsTxBufferUsedOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
      PduR_BmTxBufferArrayRamIterType txInstanceReadIdx = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);

      if(mainReadIdx == txInstanceReadIdx)
      {
        if(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) == PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM)
        {
          if(((txBufferArrayStartIdx <= txInstanceReadIdx) && (txInstanceReadIdx <= currentBeforeDestReadIdx)))
          {
            deltaInstIdxMainIdxTailMainIdx = ((txBufferArrayEndIdx - mainReadIdx) + (txInstanceReadIdx - txBufferArrayStartIdx));
            currentBeforeDestReadIdx = txInstanceReadIdx;
          }
        }
        else
        {
          bIsAnyInstanceFull = TRUE;
        }
      }

      else if((mainReadIdx < txInstanceReadIdx) && (txInstanceReadIdx < currentAfterDestReadIdx))
      {
        currentAfterDestReadIdx = txInstanceReadIdx;
        deltaInstIdxMainIdxTailInstIdx = (txInstanceReadIdx - mainReadIdx);
      }

      else if(((txBufferArrayStartIdx <= txInstanceReadIdx) && (txInstanceReadIdx < currentBeforeDestReadIdx)))
      {
        currentBeforeDestReadIdx = txInstanceReadIdx;
        deltaInstIdxMainIdxTailMainIdx = ((txBufferArrayEndIdx - mainReadIdx) + (txInstanceReadIdx - txBufferArrayStartIdx));
      }
      else
      {
      }
    }
  }
  if(!bIsAnyInstanceFull){
    if((mainReadIdx < currentAfterDestReadIdx) && (currentAfterDestReadIdx < txBufferArrayEndIdx)){
      retVal = PduR_Bm_UpdateMain_After_GetData(txBufferElementStateIdx, deltaInstIdxMainIdxTailInstIdx);
    }
    else if((txBufferArrayStartIdx <= currentBeforeDestReadIdx) && (currentBeforeDestReadIdx <= mainReadIdx)){
      retVal = PduR_Bm_UpdateMain_After_GetData(txBufferElementStateIdx, deltaInstIdxMainIdxTailMainIdx);
    }
    else{
      PduR_Det_ReportError(PDUR_GW_BUFMGR_UPDATEMAINREADIDX, PDUR_E_FATAL);
    }
  }
  else{
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_Init(void){
  PduR_Bm_Init_TxBuffer();
  PduR_Bm_Init_TxBufferInstance();
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData(PduR_BmTxBufferRomIterType txBufferElementIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr){
  BufReq_ReturnType retVal = BUFREQ_OK;
  PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx;
  switch(PduR_GetPduRBufferStateOfBmTxBufferRam(txBufferElementIdx)){
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(txBufferElementIdx, pduLength, sduDataPtr);
      break;
    }
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_PutData_StateHandler_BUFFER_EMPTY_OR_WRITE4READ(txBufferElementIdx, pduLength, sduDataPtr);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_Bm_PutData_StateHandler_BUFFER_READ4WRITE(txBufferElementIdx, pduLength, sduDataPtr);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      if(pduLength != 0u)
      {
        retVal = BUFREQ_E_NOT_OK;
      }
      break;
    }
    default:
      break;
  }
  for(bmTxBufferInstanceRomIdx = PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(txBufferElementIdx);
      bmTxBufferInstanceRomIdx < PduR_GetBmTxBufferArrayRamInstanceStopIdxOfBmTxBufferRam(txBufferElementIdx); bmTxBufferInstanceRomIdx++){
    PduR_Bm_UpdateInstance_After_PutData(bmTxBufferInstanceRomIdx, (pduLength));
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutDataAsPtr(PduR_BmTxBufferRomIterType txBufferElementIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  info->SduDataPtr = PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementIdx));
  info->SduLength = (PduLengthType) PduR_Bm_GetLinearBufferSize(txBufferElementIdx);
  return PduR_Bm_PutData(txBufferElementIdx, info->SduLength, info->SduDataPtr);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBuffer(PduR_BmTxBufferRomIterType txBufferElementStateIdx){
  PduR_SetRxLengthOfBmTxBufferRam(txBufferElementStateIdx, (PduLengthType) PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(txBufferElementStateIdx));
  PduR_SetAllocatedOfBmTxBufferRam(txBufferElementStateIdx, FALSE);
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(txBufferElementStateIdx, (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx)));
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(txBufferElementStateIdx, (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx)));
  PduR_SetPduRBufferStateOfBmTxBufferRam(txBufferElementStateIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM);
  PduR_SetBmTxBufferArrayRamInstanceStopIdxOfBmTxBufferRam(txBufferElementStateIdx, PduR_GetBmTxBufferInstanceRomStartIdxOfBmTxBufferRom(txBufferElementStateIdx));

  PDUR_DUMMY_STATEMENT(txBufferElementStateIdx);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBufferInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferRomIdxOfBmTxBufferInstanceRomType txBufferElementStateIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx);
  PduR_SetTxBufferUsedOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, FALSE);
  PduR_SetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom((txBufferElementStateIdx))));
  PduR_SetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, (PduR_GetBmTxBufferArrayRamStartIdxOfBmTxBufferRom(txBufferElementStateIdx)));
  PduR_SetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx, PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM);

  PDUR_DUMMY_STATEMENT(bmTxBufferInstanceRomIdx);
  PDUR_DUMMY_STATEMENT(txBufferElementStateIdx);
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearDataSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = 0u;
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) - PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamEndIdxOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx)) -
        PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = 0u;
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferRam(bmTxBufferRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx) - (PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx) -
                                                                             PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx));
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferRam(bmTxBufferRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferRam(bmTxBufferRomIdx);
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = 0u;
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERRAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx);
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferArrayRamIterType retVal = 0u;

  switch(PduR_GetPduRBufferStateOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx)){
    case PDUR_BUFFER_WRITE4READ_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) - PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx);
      break;
    }
    case PDUR_BUFFER_READ4WRITE_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal =
        PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx)) -
        (PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx) - PduR_GetBmTxBufferArrayRamWriteIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx));
      break;
    }
    case PDUR_BUFFER_FULL_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx));
      break;
    }
    case PDUR_BUFFER_EMPTY_PDURBUFFERSTATEOFBMTXBUFFERINSTANCERAM:
    {
      retVal = 0u;
      break;
    }
    default:
      break;
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON )

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_AllocateTxBuffer(PduR_FmFifoRomIterType fmFifoRomIdx,
                                                            PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx,
                                                            PduLengthType pduLength,
                                                            PduLengthType metaDataLength,
                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr,
                                                            P2VAR(PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType, AUTOMATIC, PDUR_APPL_DATA) allocatedTxBufferIdxPtr,
                                                            boolean considerSmallerBuffer){
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType lastSuitableBmTxBufferRomIdx = 0u;
  boolean lastSuitableBmTxBufferRomIdxFound = FALSE;
  PduR_BmTxBufferIndRomIterType bmTxBufferRomIndIdx;
  if(PduR_IsDedicatedTxBufferOfFmFifoElementRam(fmFifoElementRamWriteIdx)){
    PduR_BmTxBufferRomIterType txBufferRomIdx = PduR_GetBmTxBufferRomIdxOfFmFifoElementRam(fmFifoElementRamWriteIdx);
    PduR_SetRxLengthOfBmTxBufferRam(txBufferRomIdx, pduLength);
    *allocatedTxBufferIdxPtr = (PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType) txBufferRomIdx;
    *bufferSizePtr = (PduLengthType) PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(txBufferRomIdx);
    retVal = BUFREQ_OK;
  }
  else{
    PduR_BmTxBufferIndRomIterType bmTxBufferRomIndStartId = PduR_GetBmTxBufferIndRomStartIdxOfFmFifoRom(fmFifoRomIdx);
    PduR_BmTxBufferIndRomIterType bmTxBufferRomIndEndIdx = PduR_GetBmTxBufferIndRomEndIdxOfFmFifoRom(fmFifoRomIdx);

# if(PDUR_SPINLOCKRAM == STD_ON)
    PduR_Lock_LockBuffersByFmFifo(fmFifoRomIdx);
# endif
    {
      for(bmTxBufferRomIndIdx = bmTxBufferRomIndStartId; bmTxBufferRomIndIdx < bmTxBufferRomIndEndIdx; bmTxBufferRomIndIdx++)
      {
        PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType bmTxBufferRomIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferIndRom(bmTxBufferRomIndIdx);

        if(!PduR_IsAllocatedOfBmTxBufferRam(bmTxBufferRomIdx))
        {
          if(PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx) >= ((PduLengthType) (pduLength + metaDataLength)))
          {
            PduR_SetAllocatedOfBmTxBufferRam(bmTxBufferRomIdx, TRUE);
            PduR_SetRxLengthOfBmTxBufferRam(bmTxBufferRomIdx, pduLength);
            *allocatedTxBufferIdxPtr = bmTxBufferRomIdx;

            *bufferSizePtr = (PduLengthType) PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(bmTxBufferRomIdx);
            retVal = BUFREQ_OK;
            break;
          }
          else if(considerSmallerBuffer == TRUE)
          {
            lastSuitableBmTxBufferRomIdx = bmTxBufferRomIdx;
            lastSuitableBmTxBufferRomIdxFound = TRUE;
          }
          else
          {
          }
        }
      }

      if(retVal != BUFREQ_OK)
      {
        if(lastSuitableBmTxBufferRomIdxFound == TRUE)
        {
          PduR_SetAllocatedOfBmTxBufferRam(lastSuitableBmTxBufferRomIdx, TRUE);
          PduR_SetRxLengthOfBmTxBufferRam(lastSuitableBmTxBufferRomIdx, pduLength);
          *allocatedTxBufferIdxPtr = lastSuitableBmTxBufferRomIdx;

          *bufferSizePtr = (PduLengthType) PduR_GetBmTxBufferArrayRamLengthOfBmTxBufferRom(lastSuitableBmTxBufferRomIdx);
          retVal = BUFREQ_OK;
        }
        else
        {
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
# if(PDUR_SPINLOCKRAM == STD_ON)
    PduR_Lock_UnlockBuffersByFmFifo(fmFifoRomIdx);
# endif
  }
  return retVal;
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON )

FUNC(void, PDUR_CODE) PduR_Bm_CopyDataAsPtr(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_BmTxBufferArrayRamIterType length){
  info->SduDataPtr = PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx));
  if(length > PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx)){
    info->SduLength = (PduLengthType) PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx);
  }
  else{
    info->SduLength = (PduLengthType) length;
  }
}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON )

FUNC(void, PDUR_CODE) PduR_Bm_GetDataAsPtr(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_BmTxBufferArrayRamIterType length){
  info->SduDataPtr = PduR_GetAddrBmTxBufferArrayRam(PduR_GetBmTxBufferArrayRamReadIdxOfBmTxBufferInstanceRam(bmTxBufferInstanceRomIdx));
  if(length > PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx)){
    info->SduLength = (PduLengthType) PduR_Bm_GetLinearDataSizeInstance(bmTxBufferInstanceRomIdx);
  }
  else{
    info->SduLength = (PduLengthType) length;
  }
  (void) PduR_Bm_GetData(bmTxBufferInstanceRomIdx, info->SduLength, info->SduDataPtr);

}
#endif

#if(PDUR_BMTXBUFFERRAM == STD_ON )

FUNC(PduLengthType, PDUR_CODE) PduR_Bm_GetTotalDataTranferredLength(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx){
  PduR_BmTxBufferRomIterType txBufferElementStateIdx = PduR_GetBmTxBufferRomIdxOfBmTxBufferInstanceRom(bmTxBufferInstanceRomIdx);
  PDUR_DUMMY_STATEMENT(bmTxBufferInstanceRomIdx);
  return PduR_GetRxLengthOfBmTxBufferRam(txBufferElementStateIdx);
}

#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

