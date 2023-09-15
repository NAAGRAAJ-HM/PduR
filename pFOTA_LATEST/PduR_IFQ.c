

#define PDUR_IFQ_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_IFQ.hpp"
#include "SchM_PduR.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueFull(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueEmpty(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementReadIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementWriteIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_IFQ_Init(void){
  PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx;
  for(interfaceFifoQueueRomIdx = 0u; interfaceFifoQueueRomIdx < PduR_GetSizeOfInterfaceFifoQueueRom(); interfaceFifoQueueRomIdx++){
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue);
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue);
    PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE);
  }
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_PutFifo(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  if(PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx)){
    retVal = E_NOT_OK;
  }
  else{
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
    PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType interfaceFifoQueueElementRamWriteIdx = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);

    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType offset = (interfaceFifoQueueElementRamWriteIdx - startIdxOfQueue) * PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

    PduR_SetActualLengthOfInterfaceFifoQueueElementRam(interfaceFifoQueueElementRamWriteIdx, pduLength);
    PduR_Core_MemCpyRamToRam(PduR_GetAddrInterfaceFifoQueueArrayRam(PduR_GetInterfaceFifoQueueArrayRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)) + offset, sduDataPtr, pduLength);
    PduR_IFQ_IncrementWriteIdx(interfaceFifoQueueRomIdx);
    retVal = E_OK;
  }

  PDUR_DUMMY_STATEMENT(rmDestRomIdx);
  return retVal;
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueFull(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx){
  return PduR_IsFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueEmpty(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx){
  return (PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx) == PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx))
          && !PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx);
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementReadIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx){
  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType localReadIdx = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  localReadIdx++;

  if(localReadIdx >= PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)){
    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx));
  }
  else{
    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, localReadIdx);
  }

  PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE);
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementWriteIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx){
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType localWriteIdx = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  localWriteIdx++;

  if(localWriteIdx >= PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)){
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx));
  }
  else{
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, localWriteIdx);
  }

  if(PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx) == PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx)){
    PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, TRUE);
  }
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info){
  Std_ReturnType retVal = E_NOT_OK;
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  if(PduR_IFQ_IsQueueEmpty(interfaceFifoQueueRomIdx)){
    retVal = E_NOT_OK;
  }
  else{
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
    PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType interfaceFifoQueueElementRamReadIdx = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);

    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType offset = (interfaceFifoQueueElementRamReadIdx - startIdxOfQueue) * PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

    info->SduDataPtr = PduR_GetAddrInterfaceFifoQueueArrayRam(PduR_GetInterfaceFifoQueueArrayRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)) + offset;
    info->SduLength  = PduR_GetActualLengthOfInterfaceFifoQueueElementRam(PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx));
    *rmDestRomIdx = PduR_GetRmDestRomIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_IFQ_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  if(!PduR_IFQ_IsQueueEmpty(interfaceFifoQueueRomIdx)){
    PduR_IFQ_IncrementReadIdx(interfaceFifoQueueRomIdx);
  }
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_IFQ_FlushQueue(PduR_RmGDestRomIterType rmGDestRomIdx){
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

  PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue);
  PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue);
  PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE);
}
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(uint16, PDUR_CODE) PduR_IFQ_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx){
  uint16 fillLevel = 0;
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType  readIdx         = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType writeIdx        = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
  PduR_InterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRomType   endIdxOfQueue   = PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

  if(readIdx < writeIdx){
    fillLevel = (writeIdx - readIdx);
  }
  else if(writeIdx < readIdx){
    fillLevel = (endIdxOfQueue - readIdx) + (writeIdx - startIdxOfQueue);
  }
  else{
    if(PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx)){
      fillLevel = (endIdxOfQueue - startIdxOfQueue);
    }
    else{
      fillLevel = 0;
    }
  }

  return fillLevel;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

