#ifndef PDUR_DCM_UP_H
#define PDUR_DCM_UP_H

#include "PduR_Prv.hpp"

#define PduR_iDcmTransmitID(id)    (PDUR_DCM_TX_BASE[(id)].loId)
#define PduR_iDcmTransmitFunc(id)  (PduR_loTransmitTable[(PDUR_DCM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)
#define PduR_aDcmTransmit(id, ptr) PduR_iDcmTransmitFunc(id)(PduR_iDcmTransmitID(id), (ptr))
#define PduR_rDcmTransmit(id, ptr) PduR_aDcmTransmit((id), (ptr))
#define PDUR_IH_Dcm_Transmit_Func  PDUR_DET_API(PduR_invId_UpTransmit)

#endif

