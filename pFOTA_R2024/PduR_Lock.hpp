

#if !defined (PDUR_LOCK_H)
# define PDUR_LOCK_H

# include "Types_SwcServicePduR.hpp"
# include "CfgSwcServicePduR.hpp"
# include "SwcServicePduR_Lcfg.hpp"

# define PDUR_START_SEC_CODE
# include "MemMap.hpp"

# if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Lock_Init(void);
# endif

FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathBySrcPdu(PduR_RmSrcRomIterType rmSrcIdx);

FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathBySrcPdu(PduR_RmSrcRomIterType rmSrcIdx);

FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathByDestPdu(PduR_RmDestRomIterType rmDestIdx);

FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathByDestPdu(PduR_RmDestRomIterType rmDestIdx);

FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathByGDestPdu(PduR_RmGDestRomIterType rmGDestIdx);

FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathByGDestPdu(PduR_RmGDestRomIterType rmGDestIdx);

# if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Lock_LockBuffersByFmFifo(PduR_FmFifoRomIterType fmFifoRomIdx);
# endif

# if(PDUR_SPINLOCKRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Lock_UnlockBuffersByFmFifo(PduR_FmFifoRomIterType fmFifoRomIdx);
# endif

# define PDUR_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

