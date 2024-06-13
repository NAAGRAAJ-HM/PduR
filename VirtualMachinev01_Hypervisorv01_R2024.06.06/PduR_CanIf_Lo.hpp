#ifndef PDUR_CANIF_LO_H
#define PDUR_CANIF_LO_H

#include "PduR_Prv.hpp"

#define PduR_CanIf_upIfRxIndicationFuncId(id) (PDUR_CANIF_RXIND_BASE[(id)].upRxIndicationID)
#define PduR_iCanIfRxIndicationID(id)         (PDUR_CANIF_RXIND_BASE[(id)].upId)
#define PduR_iCanIfRxIndicationFunc(id)       (PduR_upIfRxIndicationTable[(PDUR_CANIF_RXIND_BASE[(id)].upRxIndicationID)].PduR_upIfRxIndicationFunc)
#define PduR_aCanIfRxIndication(id, ptr)      PduR_iCanIfRxIndicationFunc(id)(PduR_iCanIfRxIndicationID(id), (ptr))
#define PduR_rCanIfRxIndication(id, ptr)      PduR_aCanIfRxIndication((id), (ptr))
#define PduR_iCanIfTxConfirmationID(id)       (PDUR_CANIF_TXCONF_BASE[(id)].upId)
#define PduR_iCanIfTxConfirmationFunc(id)     (PduR_upIfTxConfirmationTable[(PDUR_CANIF_TXCONF_BASE[(id)].upTxConfirmationID)].PduR_upIfTxConfirmationFunc)
#define PduR_aCanIfTxConfirmation(id)         PduR_iCanIfTxConfirmationFunc(id)(PduR_iCanIfTxConfirmationID(id))
#define PduR_rCanIfTxConfirmation(id)         PduR_aCanIfTxConfirmation(id)

#endif

