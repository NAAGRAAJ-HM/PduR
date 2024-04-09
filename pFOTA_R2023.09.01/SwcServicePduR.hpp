#ifndef PDUR_H
#define PDUR_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "Types_SwcServicePduR.hpp"
#include "CfgSwcServicePduR.hpp"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif
#include "SwcServicePduR_Lcfg.hpp"

#define PDUR_AR_RELEASE_MAJOR_VERSION       4u
#define PDUR_AR_RELEASE_MINOR_VERSION       0u
#define PDUR_AR_RELEASE_REVISION_VERSION    3u
#define PDUR_SW_MAJOR_VERSION  13u
#define PDUR_SW_MINOR_VERSION   3u
#define PDUR_SW_PATCH_VERSION   3u
#define PDUR_VENDOR_ID           1u
#define PDUR_MODULE_ID           51u
#define PDUR_E_CONFIG_PTR_INVALID             ((uint8)0x00u)
#define PDUR_E_INVALID_REQUEST                ((uint8)0x01u)
#define PDUR_E_PDU_ID_INVALID                 ((uint8)0x02u)
#define PDUR_E_TP_TX_REQ_REJECTED             ((uint8)0x03u)
#define PDUR_E_PARAM_INVALID                  ((uint8)0x04u)
#define PDUR_E_DUPLICATE_IPDU_ID              ((uint8)0x06u)
#define PDUR_E_IPDU_TOO_LONG                  ((uint8)0x07u)
#define PDUR_E_ROUTING_PATH_GROUP_ID_INVALID  ((uint8)0x08u)
#define PDUR_E_NULL_POINTER                   ((uint8)0x09u)
#define PDUR_E_INIT_FAILED                    ((uint8)0x0Bu)
#define PDUR_E_PDU_INSTANCES_LOST             ((uint8)0x0Au)
#define PDUR_E_INVALID_CFG_DATA               ((uint8)0xA0u)
#define PDUR_E_UNEXPECTED_CALL                ((uint8)0xA1u)
#define PDUR_E_FATAL                          ((uint8)0xFFu)
#define PDUR_E_MCQ_QUEUE_OVERFLOW             ((uint8)0xB0u)
#define PDUR_E_EVC_QUEUE_OVERFLOW             ((uint8)0xB1u)
#define PDUR_E_INVALID_CORE_ID                ((uint8)0xB2u)
#define PDUR_FCT_INIT                 ((uint8)0x00u)
#define PDUR_FCT_VERSIONINFO          ((uint8)0xf1u)
#define PDUR_FCT_CONFIGURATIONID      ((uint8)0xf2u)
#define PDUR_FCT_MULTIIFRXIND         ((uint8)0x80u)
#define PDUR_FCT_RMIF_RXIND           ((uint8)0x81u)
#define PDUR_FCT_RMIF_TXCONF          ((uint8)0x82u)
#define PDUR_FCT_RMIF_TXTT            ((uint8)0x83u)
#define PDUR_FCT_RMIF_FQ              ((uint8)0x8Bu)
#define PDUR_FCT_RMTP_TPRXIND         ((uint8)0x85u)
#define PDUR_FCT_RMTP_TPTXCONF        ((uint8)0x86u)
#define PDUR_FCT_RMTP_ROUTE           ((uint8)0x87u)
#define PDUR_FCT_RMTP_SORX            ((uint8)0x88u)
#define PDUR_FCT_RMTP_CPYRX           ((uint8)0x89u)
#define PDUR_FCT_RMTP_CPYTX           ((uint8)0x8Au)
#define PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_ENDIDX   ((uint8)0x8Bu)
#define PDUR_FCT_GW_BUFMGR_PUT_BETWEEN_WRITEIDX_READIDX  ((uint8)0x8Cu)
#define PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_ENDIDX    ((uint8)0x8Du)
#define PDUR_FCT_GW_BUFMGR_GET_BETWEEN_READIDX_WRITEIDX  ((uint8)0x8Eu)
#define PDUR_FCT_RMIF_FIFOMGR_APPENDELEMENT              ((uint8)0x93u)
#define PDUR_FCT_RMIF_FIFOMGR_OVERWRITEELEMENT           ((uint8)0x94u)
#define PDUR_FCT_RMTP_TRANSMITPREPARATION                ((uint8)0x95u)
#define PDUR_FCT_PDUR_RMIF_RXINDICATION_ROUTE_FIB        ((uint8)0x96u)
#define PDUR_FCT_PDUR_RMIF_RXINDICATION_UPDATE_FIB_AND_ROUTE        ((uint8)0x97u)
#define PDUR_FCT_PDUR_RMIF_RXINDICATION_UPDATE_FIB_AND_ROUTE_MULTI  ((uint8)0x98u)
#define PDUR_FCT_PDUR_RMTP_LOANDUPTRANSMIT  ((uint8)0x99u)
#define PDUR_RMTP_TXINSTSM_TPTXCONFIRMATION_ACTIVEORABORTED ((uint8)0x9Au)
#define PDUR_RMTP_TXINSTSM_TPCANCELTRANSMIT_FATALERROR ((uint8)0x9Bu)
#define PDUR_RMTP_FIFOSM_ACTIVATENEXT_FATALERROR ((uint8)0x9Du)
#define PDUR_RMTP_RXSM_TPRXINDICATION_UNEXPECTEDCALL  ((uint8)0x9Fu)
#define PDUR_RMTP_TXINSTSM_TPTXCONFIRMATION_UNEXPECTEDCALL ((uint8)0xA2u)
#define PDUR_RMTP_FIFOSM_CHECKREADY2TRANSMIT_FATALERROR ((uint8)0xA4u)
#define PDUR_RMTP_FIFOSM_RXFINISHED_FATALERROR ((uint8)0xA5u)
#define PDUR_RMTP_FIFOSM_TXFINISHED_FATALERROR ((uint8)0xA6u)
#define PDUR_RXSM_TPCANCELRECEIVE_FATALERROR ((uint8)0xA6u)
#define PDUR_RXSM_COPYRXDATA_UNEXPECTEDCALL ((uint8)0xA7u)
#define PDUR_RMTP_TXINSTSM_COPYTXDATA_UNEXPECTEDCALL ((uint8)0xA8u)
#define PDUR_RMTP_MULTIPLESOURCEHANDLER_TPTXCONFIRMATION ((uint8)0xA9u)
#define PDUR_RMTP_MULTIPLESOURCEHANDLER_CANCELTRANSMIT ((uint8)0xAAu)
#define PDUR_RMTP_MULTIPLESOURCEHANDLER_COPYTXDATA ((uint8)0xABu)
#define PDUR_RMTP_TXINSTSM_TPTRIGGERTRANSMIT_ACTIVEORABORTED ((uint8)0xACu)
#define PDUR_RMIF_MULTIPLESOURCEHANDLER_CANCELTRANSMIT ((uint8)0xADu)
#define PDUR_TXINSTSM_COPYTXDATA_RMTXINSTACTIVE ((uint8)0xAEu)
#define PDUR_GW_BUFMGR_UPDATEMAINREADIDX ((uint8)0xAFu)
#define PDUR_RMIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT ((uint8)0xB0u)
#define PDUR_GW_BUFMGR_UPDATEMAIN_AFTER_GETDATA ((uint8)0xB1u)
#define PDUR_GW_BUFMGR_UPDATEMAIN_AFTER_GETDATA_STATEHANDLER_BUFFER_FULL_OR_READ4WRITE ((uint8)0xB2u)
#define PDUR_GW_BUFMGR_UPDATEMAIN_AFTER_GETDATA_STATEHANDLER_BUFFER_WRITE4READ ((uint8)0xB3u)
#define PDUR_RMTP_TXSM_CHECK4TXFINISH_FATALERROR  ((uint8)0xB4u)
#define PDUR_RMTP_ASSIGNASSOCIATEDBUFFER2DESTINATION  ((uint8)0xB5u)
#define PDUR_RMTP_TXINSTSM_TPTRIGGERTRANSMIT_FATALERROR ((uint8)0xB6u)
#define PDUR_FM_ACTIVATENEXT ((uint8)0xB7u)
#define PDUR_RM_TPTRIGGERTRANSMIT_FATALERROR ((uint8)0xB8u)
#define PDUR_RMIF_INIT_DEDICATEDTXBUFFER  ((uint8)0xB9u)
#define PDUR_RMIF_INIT_TTSINGLEBUFFER ((uint8)0xBAu)
#define PDUR_RMTP_INIT_DEDICATEDTXBUFFER ((uint8)0xBBu)
#define PDUR_RMIF_SINGLEBUFFERHANDLING ((uint8)0xBCu)
#define PDUR_RMIF_DFIFOANDTTFIFOHANDLING ((uint8)0xBDu)
#define PDUR_FM_FREEFIFOELEMENT ((uint8)0xBFu)
#define PDUR_FM_ACTIVATEWRITE ((uint8)0xC0u)
#define PDUR_FMFINISHREAD ((uint8)0xC1u)
#define  PDUR_FMACTIVATEREAD ((uint8)0xC2u)
#define  PDUR_RXSM_STARTOFRECEPTION ((uint8)0xC3u)
#define  PDUR_FINISHRECEPTION ((uint8)0xC4u)
#define  PDUR_FCT_CHPARA ((uint8)0xC5u)
#define  PDUR_FCT_CRX ((uint8)0xC6u)
#define PDUR_FCT_CTX ((uint8)0xC7u)
#define PDUR_FCT_TX ((uint8)0xC8u)
#define PDUR_FCT_IFRXIND ((uint8)0xC9u)
#define PDUR_FCT_IFTXCFM ((uint8)0xCAu)
#define PDUR_FCT_TT ((uint8)0xCBu)
#define PDUR_FCT_SOR ((uint8)0xCCu)
#define PDUR_FCT_CPYRX ((uint8)0xCDu)
#define PDUR_FCT_CPYTX ((uint8)0xCEu)
#define PDUR_FCT_TPRXIND ((uint8)0xCFu)
#define PDUR_FCT_TPTXCFM ((uint8)0xD0u)
#define PDUR_RMIF_MULTIPLESOURCEHANDLER_TXCONFIRMATION ((uint8)0xD3u)
#define PDUR_FCT_MAINFUNCTION_TX ((uint8)0xD4u)
#define PDUR_LOCK_LOCK ((uint8)0xD5u)
#define PDUR_LOCK_UNLOCK ((uint8)0xD5u)
#define PDUR_MCQ_WRITE_DATA ((uint8)0xDAu)
#define PDUR_MCQ_MAINFUNCTION ((uint8)0xDAu)
#define PDUR_EVC_PUT ((uint8)0xDBu)
#define PDUR_MCQ_PENDING_READ_IDX ((uint8)0xDCu)
#define PDUR_IFQ_WRITE_DATA ((uint8)0xF0u)

#if(PDUR_RPGROM == STD_ON)
#define PDUR_FCT_ENABLEROUTING        ((uint8)0x8Du)
#define PDUR_FCT_DISABLEROUTING       ((uint8)0x8Eu)
#endif

#define PDUR_E_NO_ERROR                ((uint8)0u)
#define PDUR_E_ALREADY_INITIALIZED     ((uint8)1u)
#define PDUR_INIT                      ((uint8)2u)
#define PDUR_E_UNINIT                  ((uint8)1u)
#define PDUR_E_INVALID_HANDLE          ((uint8)4u)
#define PDUR_E_PARAM_POINTER           ((uint8)9u)

#if(PDUR_DEV_ERROR_REPORT == STD_ON)
#define PduR_Det_ReportError(ApiId, ErrorCode)  (void)Det_ReportError(PDUR_MODULE_ID, 0U, (ApiId), (ErrorCode))
#define PduR_ReportRuntimeDetError(ApiId, ErrorCode) (void) Det_ReportRuntimeError(PDUR_MODULE_ID, 0U, (ApiId), (ErrorCode))
#else
#define PduR_Det_ReportError(ApiId, ErrorCode)
#define PduR_ReportRuntimeDetError(ApiId, ErrorCode)
#endif

#include "vstdlib.hpp"

#define PDUR_START_SEC_CODE
#include "MemMap.hpp"
FUNC(PduR_PBConfigIdType, PDUR_CODE) PduR_GetConfigurationId(void);
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_PBCFG) ConfigPtr);
FUNC(void, PDUR_CODE) PduR_InitMemory(void);

#if(PDUR_VERSION_INFO_API == STD_ON)
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versionInfo);
#endif

#if(PDUR_TX2LO == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_UpTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_RXIF2DEST == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
FUNC(Std_ReturnType, PDUR_CODE) PduR_LoIfTriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoIfTxConfirmation(PduIdType TxPduId);
#endif

#if(PDUR_RXTP2DEST == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength
   ,                                                            P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_RXTP2DEST == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif

#if(PDUR_RXTP2DEST == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoTpRxIndication(PduIdType id, Std_ReturnType result);
#endif

#if(PDUR_TXTP2SRC == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_LoTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry
   ,                                                      P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif

#if(PDUR_TXTP2SRC == STD_ON)
FUNC(void, PDUR_CODE) PduR_LoTpTxConfirmation(PduIdType id, Std_ReturnType result);
#endif

#if(PDUR_CANCELRECEIVESUPPORTEDOFMMROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelReceive(PduIdType id);
#endif

#if(PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);
#endif

#if((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
FUNC(Std_ReturnType, PDUR_CODE) PduR_CancelTransmit(PduIdType id);
#endif

#if(PDUR_RPGROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id);
#endif

#if(PDUR_RPGROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id);
#endif

#if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_Rm_MultipleSourceHandler_Reset(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

FUNC(Std_ReturnType, PDUR_CODE) PduR_Rm_GetSrcDestPdu(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx);

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_EvC_Put(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx, PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_EvC_WriteDeferredEventCache(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest);
#endif

#if(PDUR_DEFERREDEVENTCACHEROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_EvC_Get(PduR_DeferredEventCacheRomIdxOfSrcCoreRomType deferredEventCacheIdx, P2VAR(PduR_RmGDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmGDestRomIdxPtr);
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
#endif

