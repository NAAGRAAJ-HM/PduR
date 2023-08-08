

#if !defined (PDUR_BM_H)
# define PDUR_BM_H

# include "Types_SwcServicePduR.hpp"
# include "CfgSwcServicePduR.hpp"
# if(PDUR_DEV_ERROR_REPORT == STD_ON)
#  include "SwcServiceDet.hpp"
# endif
# include "SwcServicePduR_Lcfg.hpp"

# define PDUR_START_SEC_CODE
# include "MemMap.hpp"

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_Init(void);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutData(PduR_BmTxBufferRomIterType txBufferElementIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_PutDataAsPtr(PduR_BmTxBufferRomIterType txBufferElementIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_GetData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_CopyData(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, PduR_BmTxBufferArrayRamIterType pduLength, CONST(SduDataPtrType, AUTOMATIC) sduDataPtr);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBuffer(PduR_BmTxBufferRomIterType txBufferElementStateIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_ResetTxBufferInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_AssignAssociatedBuffer2DestinationInstance(PduR_BmTxBufferRomIterType bmTxBufferRomIdx, PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearDataSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetLinearDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalDataSizeInstance(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduR_BmTxBufferArrayRamIterType, PDUR_CODE) PduR_Bm_GetTotalBufferSize(PduR_BmTxBufferRomIterType bmTxBufferRomIdx);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_Bm_AllocateTxBuffer(PduR_FmFifoRomIterType fmFifoRomIdx,
                                                            PduR_FmFifoElementRamIterType fmFifoElementRamWriteIdx,
                                                            PduLengthType pduLength,
                                                            PduLengthType metaDataLength,
                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr,
                                                            P2VAR(PduR_BmTxBufferRomIdxOfBmTxBufferIndRomType, AUTOMATIC, PDUR_APPL_DATA) allocatedTxBufferIdxPtr,
                                                            boolean considerSmallerBuffer);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_CopyDataAsPtr(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_BmTxBufferArrayRamIterType length);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(void, PDUR_CODE) PduR_Bm_GetDataAsPtr(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduR_BmTxBufferArrayRamIterType length);
# endif

# if(PDUR_BMTXBUFFERRAM == STD_ON)

FUNC(PduLengthType, PDUR_CODE) PduR_Bm_GetTotalDataTranferredLength(PduR_BmTxBufferInstanceRomIterType bmTxBufferInstanceRomIdx);
# endif

# define PDUR_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

