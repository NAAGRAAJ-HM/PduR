

#define PDUR_MCQ_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_McQ.hpp"
#include "PduR_RmIf.hpp"
#include "SchM_PduR.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
# include "SwcServiceDet.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(uint8, PDUR_CODE) PduR_McQ_GetTxConfirmationSize(void);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(uint8, PDUR_CODE) PduR_McQ_GetDataHeaderSize(void);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_WriteUnusedHeader(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_SerializeData(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx, PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx,
                                                          CONSTP2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_SerializeTxConfirmation(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx, PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_GetWriteIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcqBufferRomIdx,
                                                                  P2VAR(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType, AUTOMATIC, PDUR_APPL_DATA) writeIdx, PduLengthType pduLengthWithHeader);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_DeserializeData(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType readIdx, P2VAR(PduR_RmDestRomEndIdxOfRmSrcRomType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx,
                                                            P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_UpdateWriteIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(PduR_RmSrcRomIdxOfRmDestRomType, PDUR_CODE) PduR_McQ_ReadTxConfirmation(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx,
                                                                                          PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType readIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_ReadData(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx, PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType readIdx,
                                                     P2VAR(PduR_RmDestRomEndIdxOfRmSrcRomType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_GetReadIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcqBufferRomIdx,
                                                                 P2VAR(PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType, AUTOMATIC, PDUR_APPL_DATA) readIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_UpdateReadIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQBufferArrayRamWrite(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx, uint8 byteToBeWritten);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetMcQBufferArrayRamPendingReadIdx(PduR_McQBufferRomIterType mcQBufferRomIdx, PduR_McQBufferArrayRamPendingReadIdxOfMcQBufferRamType readIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_McQ_Init(void){
  PduR_McQBufferRomIterType mcqBufferRomIdx;
  for(mcqBufferRomIdx = 0u; mcqBufferRomIdx < PduR_GetSizeOfMcQBufferRom(); mcqBufferRomIdx++){
    PduR_McQBufferArrayRamStartIdxOfMcQBufferRomType startIdxOfBuffer = PduR_GetMcQBufferArrayRamStartIdxOfMcQBufferRom(mcqBufferRomIdx);

    PduR_SetMcQBufferArrayRamPendingWriteIdxOfMcQBufferRam(mcqBufferRomIdx, startIdxOfBuffer);
    PduR_SetMcQBufferArrayRamPendingReadIdx(mcqBufferRomIdx, startIdxOfBuffer);
    PduR_SetMcQBufferArrayRamReadIdxOfMcQBufferRam(mcqBufferRomIdx, startIdxOfBuffer);
    PduR_SetMcQBufferArrayRamWriteIdxOfMcQBufferRam(mcqBufferRomIdx, startIdxOfBuffer);
  }
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_WriteTxConfirmation(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx, PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx;

  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();

  if(PduR_McQ_GetWriteIdx(mcQBufferRomIdx, &writeIdx, PduR_McQ_GetTxConfirmationSize()) == E_OK){
    PduR_McQ_SerializeTxConfirmation(writeIdx, rmSrcRomIdx);

    PduR_McQ_UpdateWriteIdx(mcQBufferRomIdx);
    retVal = E_OK;
  }

  else{
    retVal = E_NOT_OK;
  }
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
  return retVal;
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_WriteData(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx, PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx,
                                                   CONSTP2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data){
  uint8 errorId = PDUR_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx;

# if(PDUR_DEV_ERROR_DETECT == STD_ON)
  if(data == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(data->SduDataPtr == NULL_PTR){
    errorId = PDUR_E_PARAM_POINTER;
  }

  else
# endif
  {
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();

    if(PduR_McQ_GetWriteIdx(mcQBufferRomIdx, &writeIdx, data->SduLength + PduR_McQ_GetDataHeaderSize()) == E_OK){
      PduR_McQ_SerializeData(writeIdx, rmDestRomIdx, data);
      PduR_McQ_UpdateWriteIdx(mcQBufferRomIdx);
      retVal = E_OK;
    }

    else{
      retVal = E_NOT_OK;
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
  }

# if(PDUR_DEV_ERROR_REPORT == STD_ON)

  if(errorId != PDUR_E_NO_ERROR){
    PduR_Det_ReportError(PDUR_MCQ_WRITE_DATA, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);

  return retVal;
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_GetWriteIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcqBufferRomIdx,
                                                                  P2VAR(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType, AUTOMATIC, PDUR_APPL_DATA) writeIdx, PduLengthType pduLengthWithHeader){
  Std_ReturnType retVal = E_NOT_OK;

  PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType readIdx = PduR_GetMcQBufferArrayRamReadIdxOfMcQBufferRam(mcqBufferRomIdx);
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType localWriteIdx = PduR_GetMcQBufferArrayRamWriteIdxOfMcQBufferRam(mcqBufferRomIdx);

  PduR_McQBufferArrayRamStartIdxOfMcQBufferRomType startIdxOfBuffer = PduR_GetMcQBufferArrayRamStartIdxOfMcQBufferRom(mcqBufferRomIdx);
  PduR_McQBufferArrayRamEndIdxOfMcQBufferRomType endIdxOfBuffer = PduR_GetMcQBufferArrayRamEndIdxOfMcQBufferRom(mcqBufferRomIdx) - 1u;

  if(((localWriteIdx + 1u) == readIdx) || ((readIdx == startIdxOfBuffer) && (localWriteIdx == endIdxOfBuffer))){
    retVal = E_NOT_OK;
  }

  else if(localWriteIdx < readIdx){
    PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType linearBufferSize = readIdx - localWriteIdx - 1u;

    if(linearBufferSize >= pduLengthWithHeader){
      *writeIdx = localWriteIdx;

      PduR_SetMcQBufferArrayRamPendingWriteIdxOfMcQBufferRam(mcqBufferRomIdx, localWriteIdx + pduLengthWithHeader);
      retVal = E_OK;
    }

    else{
      retVal = E_NOT_OK;
    }
  }

  else{
    PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType linearBufferSizeAtEnd;
    PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType linearBufferSizeAtFront;

    linearBufferSizeAtEnd = (localWriteIdx == endIdxOfBuffer) ? 0u : (endIdxOfBuffer - localWriteIdx);
    linearBufferSizeAtFront = (readIdx == startIdxOfBuffer) ? 0u : (readIdx - startIdxOfBuffer - 1u);

    if(linearBufferSizeAtEnd >= pduLengthWithHeader){
      *writeIdx = localWriteIdx;

      PduR_SetMcQBufferArrayRamPendingWriteIdxOfMcQBufferRam(mcqBufferRomIdx, localWriteIdx + pduLengthWithHeader);
      retVal = E_OK;
    }

    else if(linearBufferSizeAtFront >= pduLengthWithHeader){
      PduR_McQ_WriteUnusedHeader(localWriteIdx);

      *writeIdx = startIdxOfBuffer;

      PduR_SetMcQBufferArrayRamPendingWriteIdxOfMcQBufferRam(mcqBufferRomIdx, (PduR_McQBufferArrayRamPendingWriteIdxOfMcQBufferRamType) startIdxOfBuffer + pduLengthWithHeader);

      retVal = E_OK;
    }

    else{
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(uint8, PDUR_CODE) PduR_McQ_GetDataHeaderSize(void){
  return PDUR_MCQ_SIZE_OF_HEADER + sizeof(PduR_RmDestRomEndIdxOfRmSrcRomType) + sizeof(PduLengthType);
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(uint8, PDUR_CODE) PduR_McQ_GetTxConfirmationSize(void){
  return PDUR_MCQ_SIZE_OF_HEADER + sizeof(PduR_RmSrcRomIdxOfRmDestRomType);
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_WriteUnusedHeader(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx){
  PduR_McQBufferArrayRamWrite(writeIdx, PDUR_MCQ_UNUSED_HEADER);
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_SerializeData(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx, PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx,
                                                          CONSTP2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data){
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdxIntern = writeIdx;

  PduR_McQBufferArrayRamWrite(writeIdxIntern, PDUR_MCQ_DATA_HEADER);
  writeIdxIntern++;

  {
    uint8 rmDestRomIterator = 0u;
    PduR_RmDestRomEndIdxOfRmSrcRomType tempRmDestRomIdx = rmDestRomIdx;
    uint8 shiftOperand = 0u;
    for(; rmDestRomIterator < sizeof(PduR_RmDestRomEndIdxOfRmSrcRomType); rmDestRomIterator++){
      tempRmDestRomIdx = tempRmDestRomIdx >> shiftOperand;
      PduR_McQBufferArrayRamWrite(writeIdxIntern, (uint8) tempRmDestRomIdx);
      shiftOperand = 8u;
      writeIdxIntern++;
    }
  }

  {
    uint8 pduLengthTypeIterator = 0u;
    PduLengthType tempPduLength = data->SduLength;
    for(; pduLengthTypeIterator < sizeof(PduLengthType); pduLengthTypeIterator++){
      PduR_McQBufferArrayRamWrite(writeIdxIntern, (uint8) tempPduLength);
      tempPduLength = tempPduLength >> 8u;
      writeIdxIntern++;
    }
  }

  if((writeIdxIntern + data->SduLength) < PduR_GetSizeOfMcQBufferArrayRam()){
    VStdMemCpyRamToRam(PduR_GetAddrMcQBufferArrayRam(writeIdxIntern), data->SduDataPtr, data->SduLength);
  }
  else{
    PduR_Det_ReportError(PDUR_MCQ_WRITE_DATA, PDUR_E_FATAL);
  }
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_SerializeTxConfirmation(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx, PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx){
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdxIntern = writeIdx;

  PduR_McQBufferArrayRamWrite(writeIdxIntern, PDUR_MCQ_TXCONFIRMATION_HEADER);
  writeIdxIntern++;

  {
    uint8 rmSrcRomIterator = 0u;
    uint8 shiftOperand = 0u;
    PduR_RmSrcRomIdxOfRmDestRomType tempRmSrcRomIdx = rmSrcRomIdx;
    for(; rmSrcRomIterator < sizeof(PduR_RmSrcRomIdxOfRmDestRomType); rmSrcRomIterator++){
      tempRmSrcRomIdx = tempRmSrcRomIdx >> shiftOperand;
      PduR_McQBufferArrayRamWrite(writeIdxIntern, (uint8) tempRmSrcRomIdx);
      shiftOperand = 8u;
      writeIdxIntern++;
    }
  }
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_DeserializeData(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType readIdx, P2VAR(PduR_RmDestRomEndIdxOfRmSrcRomType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx,
                                                            P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data){
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType readIdxIntern = readIdx;

  readIdxIntern += PDUR_MCQ_SIZE_OF_HEADER;

  {
    uint8 rmDestRomIterator = 0u;
    PduR_RmDestRomEndIdxOfRmSrcRomType tempRmDestRomIdx = 0u;
    uint8 offset = 0u;
    for(; rmDestRomIterator < sizeof(PduR_RmDestRomEndIdxOfRmSrcRomType); rmDestRomIterator++){
      tempRmDestRomIdx = tempRmDestRomIdx | (((PduR_RmDestRomEndIdxOfRmSrcRomType) PduR_GetMcQBufferArrayRam(readIdxIntern)) << offset);
      offset += 8u;
      readIdxIntern++;
    }
    *rmDestRomIdx = tempRmDestRomIdx;
  }

  {
    uint8 pduLengthTypeIterator = 0u;
    PduLengthType tempPduLength = 0u;
    uint8 offset = 0u;
    for(; pduLengthTypeIterator < sizeof(PduLengthType); pduLengthTypeIterator++){
      tempPduLength = tempPduLength | (((PduLengthType) PduR_GetMcQBufferArrayRam(readIdxIntern)) << offset);
      offset += 8u;
      readIdxIntern++;
    }
    data->SduLength = tempPduLength;
  }

  data->SduDataPtr = PduR_GetAddrMcQBufferArrayRam(readIdxIntern);
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(PduR_RmSrcRomIdxOfRmDestRomType, PDUR_CODE) PduR_McQ_ReadTxConfirmation(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx,
                                                                                          PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType readIdx){
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType readIdxIntern = readIdx;

  readIdxIntern += PDUR_MCQ_SIZE_OF_HEADER;

  {
    uint8 rmSrcRomIterator = 0u;
    PduR_RmSrcRomIdxOfRmDestRomType tempRmSrcRomIdx = 0u;
    uint8 offset = 0u;
    for(; rmSrcRomIterator < sizeof(PduR_RmSrcRomIdxOfRmDestRomType); rmSrcRomIterator++){
      tempRmSrcRomIdx = tempRmSrcRomIdx | (((PduR_RmSrcRomIdxOfRmDestRomType) PduR_GetMcQBufferArrayRam(readIdxIntern)) << offset);
      offset += 8u;
      readIdxIntern++;
    }

    PduR_SetMcQBufferArrayRamPendingReadIdx(mcQBufferRomIdx, readIdxIntern);
    return tempRmSrcRomIdx;
  }
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_ReadData(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx, PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType readIdx,
                                                     P2VAR(PduR_RmDestRomEndIdxOfRmSrcRomType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data){
  PduR_McQ_DeserializeData(readIdx, rmDestRomIdx, data);

  PduR_SetMcQBufferArrayRamPendingReadIdx(mcQBufferRomIdx, readIdx + PduR_McQ_GetDataHeaderSize() + data->SduLength);
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_GetReadIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcqBufferRomIdx,
                                                                 P2VAR(PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType, AUTOMATIC, PDUR_APPL_DATA) readIdx){
  Std_ReturnType retVal = E_NOT_OK;

  PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType localReadIdx = PduR_GetMcQBufferArrayRamReadIdxOfMcQBufferRam(mcqBufferRomIdx);
  PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx = PduR_GetMcQBufferArrayRamWriteIdxOfMcQBufferRam(mcqBufferRomIdx);

  if(localReadIdx == writeIdx){
    retVal = E_NOT_OK;
  }

  else{
    if(PduR_GetMcQBufferArrayRam(localReadIdx) == PDUR_MCQ_UNUSED_HEADER){
      localReadIdx = PduR_GetMcQBufferArrayRamStartIdxOfMcQBufferRom(mcqBufferRomIdx);
    }
    *readIdx = localReadIdx;
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_UpdateReadIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx){
  PduR_SetMcQBufferArrayRamReadIdxOfMcQBufferRam(mcQBufferRomIdx, PduR_GetMcQBufferArrayRamPendingReadIdxOfMcQBufferRam(mcQBufferRomIdx));
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQBufferArrayRamWrite(PduR_McQBufferArrayRamWriteIdxOfMcQBufferRamType writeIdx, uint8 byteToBeWritten){
  if(writeIdx < PduR_GetSizeOfMcQBufferArrayRam()){
    PduR_SetMcQBufferArrayRam(writeIdx, byteToBeWritten);
  }
  else{
    PduR_Det_ReportError(PDUR_MCQ_WRITE_DATA, PDUR_E_FATAL);
  }
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_McQ_UpdateWriteIdx(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx){
  PduR_SetMcQBufferArrayRamWriteIdxOfMcQBufferRam(mcQBufferRomIdx, PduR_GetMcQBufferArrayRamPendingWriteIdxOfMcQBufferRam(mcQBufferRomIdx));
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_SetMcQBufferArrayRamPendingReadIdx(PduR_McQBufferRomIterType mcQBufferRomIdx, PduR_McQBufferArrayRamPendingReadIdxOfMcQBufferRamType readIdx){
  if(readIdx < PduR_GetMcQBufferArrayRamEndIdxOfMcQBufferRom(mcQBufferRomIdx)){
    PduR_SetMcQBufferArrayRamPendingReadIdxOfMcQBufferRam(mcQBufferRomIdx, readIdx);
  }
  else{
    PduR_Det_ReportError(PDUR_MCQ_PENDING_READ_IDX, PDUR_E_FATAL);
  }
}
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_McQ_MainFunction(PduR_CoreManagerRomIdxOfMmRomType coreManagerRomIdx){
  PduR_SrcCoreRomEndIdxOfCoreManagerRomType srcCoreRomIdx;

  for(srcCoreRomIdx = PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx < PduR_GetSrcCoreRomEndIdxOfCoreManagerRom(coreManagerRomIdx); srcCoreRomIdx++){
    if(PduR_IsMcQBufferRomUsedOfSrcCoreRom(srcCoreRomIdx)){
      PduR_McQBufferArrayRamReadIdxOfMcQBufferRamType readIdx = 0;
      PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx = PduR_GetMcQBufferRomIdxOfSrcCoreRom(srcCoreRomIdx);

      PduR_McQBufferArrayRamLengthOfMcQBufferRomType readThreshold = PduR_GetMcQBufferArrayRamLengthOfMcQBufferRom(mcQBufferRomIdx);
      PduLengthType numberOfReadBytes = 0;

      while(PduR_McQ_GetReadIdx(mcQBufferRomIdx, &readIdx) == E_OK)
      {
        switch(PduR_GetMcQBufferArrayRam(readIdx))
        {
          case PDUR_MCQ_DATA_HEADER:
          {
            PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx;
            PduInfoType info;

            PduR_McQ_ReadData(mcQBufferRomIdx, readIdx, &rmDestRomIdx, &info);
            (void) PduR_RmIf_DispatchIfDestPdu(rmDestRomIdx, &info);
            PduR_McQ_UpdateReadIdx(mcQBufferRomIdx);

            numberOfReadBytes += ((PduLengthType) PduR_McQ_GetDataHeaderSize()) + info.SduLength;
            break;
          }

          case PDUR_MCQ_TXCONFIRMATION_HEADER:
          {
            PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_McQ_ReadTxConfirmation(mcQBufferRomIdx, readIdx);
            PduR_McQ_UpdateReadIdx(mcQBufferRomIdx);
            PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx));

            numberOfReadBytes += ((PduLengthType) PduR_McQ_GetTxConfirmationSize());
            break;
          }

          default:
            PduR_Det_ReportError(PDUR_MCQ_MAINFUNCTION, PDUR_E_FATAL);

            break;
        }

        if(numberOfReadBytes > readThreshold)
        {
          break;
        }
      }
    }
  }
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

