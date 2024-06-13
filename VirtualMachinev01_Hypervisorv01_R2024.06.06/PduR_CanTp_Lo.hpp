#ifndef PDUR_CANTP_LO_H
#define PDUR_CANTP_LO_H

#include "PduR_Prv.hpp"

#define PduR_iCanTpCopyRxDataID(id)        (PDUR_CANTP_RXIND_BASE[(id)].upId)
#define PduR_iCanTpCopyRxDataFunc(id)      (PduR_upTpCopyRxDataTable[(PDUR_CANTP_RXIND_BASE[(id)].upProvideRxBufID)].PduR_upTpCopyRxDataFunc)
#define PduR_aCanTpCopyRxData(id,info,bufSizePtr)   PduR_iCanTpCopyRxDataFunc(id)(PduR_iCanTpCopyRxDataID(id),(info),(bufSizePtr))
#define PduR_rCanTpCopyRxData(id,info,bufSizePtr)   PduR_aCanTpCopyRxData((id),(info),(bufSizePtr))
#define PduR_iCanTpStartOfReceptionID(id)        (PDUR_CANTP_RXIND_BASE[(id)].upId)
#define PduR_iCanTpStartOfReceptionFunc(id)      (PduR_upTpStartOfReceptionTable[(PDUR_CANTP_RXIND_BASE[(id)].upStartOfReceptionID)].PduR_upTpStartOfReceptionFunc)
#define PduR_aCanTpStartOfReception(id,info,TpSduLength,bufSizePtr)   PduR_iCanTpStartOfReceptionFunc(id)(PduR_iCanTpStartOfReceptionID(id),(info),(TpSduLength),(bufSizePtr))
#define PduR_rCanTpStartOfReception(id,info,TpSduLength,bufSizePtr)   PduR_aCanTpStartOfReception((id),(info),(TpSduLength),(bufSizePtr))
#define PduR_iCanTpRxIndicationID(id)           (PDUR_CANTP_RXIND_BASE[(id)].upId)
#define PduR_iCanTpRxIndicationFunc(id)         (PduR_upTpRxIndicationTable[(PDUR_CANTP_RXIND_BASE[(id)].upRxIndicationID)].PduR_upTpRxIndicationFunc)
#define PduR_aCanTpRxIndication(id,result)      PduR_iCanTpRxIndicationFunc(id)(PduR_iCanTpRxIndicationID(id), (result))
#define PduR_rCanTpRxIndication(id,result)       PduR_aCanTpRxIndication((id),(result))
#define PduR_iCanTpCopyTxDataID(id)        (PDUR_CANTP_TXCONF_BASE[(id)].upId)
#define PduR_iCanTpCopyTxDataFunc(id)      (PduR_upTpCopyTxDataTable[(PDUR_CANTP_TXCONF_BASE[(id)].upProvideTxBufID)].PduR_upTpCopyTxDataFunc)
#define PduR_aCanTpCopyTxData(id,info,retry,avdataptr)    PduR_iCanTpCopyTxDataFunc(id)(PduR_iCanTpCopyTxDataID(id), (info),(retry),(avdataptr))
#define PduR_rCanTpCopyTxData(id,info,retry,avdataptr)     PduR_aCanTpCopyTxData((id),(info),(retry),(avdataptr))
#define PduR_iCanTpTxConfirmationID(id)         (PDUR_CANTP_TXCONF_BASE[(id)].upId)
#define PduR_iCanTpTxConfirmationFunc(id)       (PduR_upTpTxConfirmationTable[(PDUR_CANTP_TXCONF_BASE[(id)].upTxConfirmationID)].PduR_upTpTxConfirmationFunc)
#define PduR_aCanTpTxConfirmation(id,result)    PduR_iCanTpTxConfirmationFunc(id)(PduR_iCanTpTxConfirmationID(id), (result))
#define PduR_rCanTpTxConfirmation(id, result)    PduR_aCanTpTxConfirmation((id),(result))
#define PDUR_IH_CanTpRx_StartOfReception_Func   PDUR_DET_API(PduR_invId_TpStartOfReception)
#define PDUR_IH_CanTpRx_CopyRxData_Func            PDUR_DET_API(PduR_invId_TpCopyRxData)
#define PDUR_IH_CanTpRx_RxIndication_Func       PDUR_DET_API(PduR_invId_TpRxIndication)
#define PDUR_IH_CanTpTx_CopyTxData_Func            PDUR_DET_API(PduR_invId_TpCopyTxData)
#define PDUR_IH_CanTpTx_TxConfirmation_Func     PDUR_DET_API(PduR_invId_TpTxConfirmation)

#endif

