#ifndef PDUR_COM_UP_H
#define PDUR_COM_UP_H

#include "PduR_Prv.hpp"

#define PduR_iComTransmitID(id)           (PDUR_COM_TX_BASE[(id)].loId)
#define PduR_iComTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_COM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)
#define PduR_rComTransmit(id, ptr)        PduR_iComTransmitFunc(id)(PduR_iComTransmitID(id), (ptr))

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_MF_Com_Transmit_Func(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
);

#define PDUR_IH_Com_Transmit_Func    PDUR_DET_API(PduR_invId_UpTransmit)

#endif

