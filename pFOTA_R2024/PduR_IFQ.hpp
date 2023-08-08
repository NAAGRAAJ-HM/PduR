

#if !defined (PDUR_IFQ_H)
# define PDUR_IFQ_H

# include "Types_SwcServicePduR.hpp"
# include "CfgSwcServicePduR.hpp"
# include "SwcServicePduR_Lcfg.hpp"

# define PDUR_START_SEC_CODE
# include "MemMap.hpp"

# if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_IFQ_Init(void);
# endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_PutFifo(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_IFQ_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_IFQ_FlushQueue(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)

FUNC(uint16, PDUR_CODE) PduR_IFQ_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

# define PDUR_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

