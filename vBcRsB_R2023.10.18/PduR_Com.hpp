#ifndef PDUR_COM_H
#define PDUR_COM_H

#include "PduR.hpp"
#include "Com.hpp"

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) ptr );

#endif
