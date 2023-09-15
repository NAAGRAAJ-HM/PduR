

#define PDUR_LOCK_SOURCE

#include "SwcServicePduR.hpp"
#include "PduR_Lock.hpp"
#include "SchM_PduR.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif
#if(PDUR_SPINLOCKRAM == STD_ON)
#include "SwcServiceOs.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) Appl_GetSpinlock(P2VAR(uint32, AUTOMATIC, PDUR_APPL_DATA) lockVar);
#endif

#if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) Appl_ReleaseSpinlock(P2VAR(uint32, AUTOMATIC, PDUR_APPL_DATA) lockVar);
#endif

#if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(uint32, PDUR_CODE) Appl_GetSpinlockInitVal(void);
#endif

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Lock(PduR_LockRomIterType lockIdx);

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Unlock(PduR_LockRomIterType lockIdx);

#if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Lock_Init(void){
  PduR_SpinlockRamIterType spinlockRamIdx;
  uint32 spinLockInitValue = Appl_GetSpinlockInitVal();

  for(spinlockRamIdx = 0u; spinlockRamIdx < PduR_GetSizeOfSpinlockRam(); spinlockRamIdx++){
    VStdLib_MemClr(PduR_GetAddrCounterOfSpinlockRam(spinlockRamIdx), PDUR_MAX_NUMBER_OF_CORES);
    PduR_SetLockVariableOfSpinlockRam(spinlockRamIdx, spinLockInitValue);
  }
}
#endif

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Lock(PduR_LockRomIterType lockIdx){
#if(PDUR_SPINLOCKRAM == STD_ON)
  if(!PduR_IsExclusiveAreaRomUsedOfLockRom(lockIdx)){
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
    {
      uint8 core_id = (uint8) GetCoreID();
      if(core_id < (uint8) PDUR_MAX_NUMBER_OF_CORES)
      {
        PduR_SpinlockRamIterType spinlockIdx = PduR_GetSpinlockRamIdxOfLockRom(lockIdx);
        if(0u == PduR_GetCounterOfSpinlockRam(spinlockIdx)[core_id])
        {
          if(E_OK != Appl_GetSpinlock(PduR_GetAddrLockVariableOfSpinlockRam(spinlockIdx)))
          {
            PduR_Det_ReportError(PDUR_LOCK_LOCK, PDUR_E_FATAL);
          }
        }
        PduR_GetCounterOfSpinlockRam(spinlockIdx)[core_id]++;
      }
      else
      {
        PduR_Det_ReportError(PDUR_LOCK_LOCK, PDUR_E_FATAL);
      }
    }
  }
  else
#endif
  {
    PduR_GetLockOfExclusiveAreaRom(PduR_GetExclusiveAreaRomIdxOfLockRom(lockIdx)) ();
  }
  PDUR_DUMMY_STATEMENT(lockIdx);
}

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Unlock(PduR_LockRomIterType lockIdx){
#if(PDUR_SPINLOCKRAM == STD_ON)
  if(!PduR_IsExclusiveAreaRomUsedOfLockRom(lockIdx)){
    {
      uint8 core_id = (uint8) GetCoreID();
      if(core_id < (uint8) PDUR_MAX_NUMBER_OF_CORES)
      {
        PduR_SpinlockRamIterType spinlockIdx = PduR_GetSpinlockRamIdxOfLockRom(lockIdx);
        if(1u == PduR_GetCounterOfSpinlockRam(spinlockIdx)[core_id])
        {
          if(E_OK != Appl_ReleaseSpinlock(PduR_GetAddrLockVariableOfSpinlockRam(spinlockIdx)))
          {
            PduR_Det_ReportError(PDUR_LOCK_UNLOCK, PDUR_E_FATAL);
          }
        }
        PduR_GetCounterOfSpinlockRam(spinlockIdx)[core_id]--;
      }
      else
      {
        PduR_Det_ReportError(PDUR_LOCK_UNLOCK, PDUR_E_FATAL);
      }
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
  }
  else
#endif
  {
    PduR_GetUnlockOfExclusiveAreaRom(PduR_GetExclusiveAreaRomIdxOfLockRom(lockIdx)) ();
  }
  PDUR_DUMMY_STATEMENT(lockIdx);
}

FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathBySrcPdu(PduR_RmSrcRomIterType rmSrcIdx){
  PduR_Lock_Lock(PduR_GetLockRomIdxOfRmSrcRom(rmSrcIdx));
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
}

FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathBySrcPdu(PduR_RmSrcRomIterType rmSrcIdx){
  PduR_Lock_Unlock(PduR_GetLockRomIdxOfRmSrcRom(rmSrcIdx));
  PDUR_DUMMY_STATEMENT(rmSrcIdx);
}

FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathByDestPdu(PduR_RmDestRomIterType rmDestIdx){
  PduR_Lock_Lock(PduR_GetLockRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)));
  PDUR_DUMMY_STATEMENT(rmDestIdx);
}

FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathByDestPdu(PduR_RmDestRomIterType rmDestIdx){
  PduR_Lock_Unlock(PduR_GetLockRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)));
  PDUR_DUMMY_STATEMENT(rmDestIdx);
}

FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathByGDestPdu(PduR_RmGDestRomIterType rmGDestIdx){
  PduR_Lock_Lock(PduR_GetLockRomIdxOfRmGDestRom(rmGDestIdx));
  PDUR_DUMMY_STATEMENT(rmGDestIdx);
}

FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathByGDestPdu(PduR_RmGDestRomIterType rmGDestIdx){
  PduR_Lock_Unlock(PduR_GetLockRomIdxOfRmGDestRom(rmGDestIdx));
  PDUR_DUMMY_STATEMENT(rmGDestIdx);
}

#if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Lock_LockBuffersByFmFifo(PduR_FmFifoRomIterType fmFifoRomIdx){
  if(PduR_IsLockRomUsedOfFmFifoRom(fmFifoRomIdx)){
    PduR_Lock_Lock(PduR_GetLockRomIdxOfFmFifoRom(fmFifoRomIdx));
  }
  PDUR_DUMMY_STATEMENT(fmFifoRomIdx);
}
#endif

#if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Lock_UnlockBuffersByFmFifo(PduR_FmFifoRomIterType fmFifoRomIdx){
  if(PduR_IsLockRomUsedOfFmFifoRom(fmFifoRomIdx)){
    PduR_Lock_Unlock(PduR_GetLockRomIdxOfFmFifoRom(fmFifoRomIdx));
  }
  PDUR_DUMMY_STATEMENT(fmFifoRomIdx);
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

