#ifndef PDUR_DCM_H
#define PDUR_DCM_H

#include "PduR.hpp"
#include "Dcm.hpp"
#include "Dcm_Cbk.hpp"

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr
);

#endif
