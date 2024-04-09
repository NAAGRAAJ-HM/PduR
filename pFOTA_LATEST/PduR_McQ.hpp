

#if !defined (PDUR_MCQ_H)
#define PDUR_MCQ_H

#include "Types_SwcServicePduR.hpp"
#include "CfgSwcServicePduR.hpp"
#include "SwcServicePduR_Lcfg.hpp"

#define PDUR_MCQ_UNUSED_HEADER         0x00u
#define PDUR_MCQ_DATA_HEADER           0x01u
#define PDUR_MCQ_TXCONFIRMATION_HEADER 0x02u
#define PDUR_MCQ_SIZE_OF_HEADER        0x01u

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_McQ_Init(void);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_WriteData(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx, PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx
   ,                                                  CONSTP2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) data);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(Std_ReturnType, PDUR_CODE) PduR_McQ_WriteTxConfirmation(PduR_McQBufferRomIdxOfSrcCoreRomType mcQBufferRomIdx, PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx);
#endif

#if(PDUR_MCQBUFFERROM == STD_ON)

FUNC(void, PDUR_CODE) PduR_McQ_MainFunction(PduR_CoreManagerRomIdxOfMmRomType coreManagerRomIdx);
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"
#endif

