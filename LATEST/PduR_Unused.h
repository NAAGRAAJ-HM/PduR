#pragma once
/*****************************************************/
/* File   : PduR_Unused.h                            */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "Std_Types.h"
#include "Compiler_Cfg_PduR.h"

/*****************************************************/
/* #DEFINES                                          */
/*****************************************************/

/*****************************************************/
/* MACROS                                            */
/*****************************************************/

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
class class_PduR_Unused{
   public:
/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
      FUNC(void, PDUR_CODE) GetVersinInfo      (void);
      FUNC(void, PDUR_CODE) GetConfigurationId (void);
      FUNC(void, PDUR_CODE) DisableRouting     (void);
      FUNC(void, PDUR_CODE) EnableRouting      (void);
      FUNC(void, PDUR_CODE) Transmit           (void);
      FUNC(void, PDUR_CODE) CancelTransmit     (void);
      FUNC(void, PDUR_CODE) CancelReceive      (void);
      FUNC(void, PDUR_CODE) RxIndication       (void);
      FUNC(void, PDUR_CODE) TxConfirmation     (void);
      FUNC(void, PDUR_CODE) TriggerTrasnmit    (void);
      FUNC(void, PDUR_CODE) TpCopyRxData       (void);
      FUNC(void, PDUR_CODE) TpRxIndication     (void);
      FUNC(void, PDUR_CODE) TpStartOfReception (void);
      FUNC(void, PDUR_CODE) TpCopyTxData       (void);
      FUNC(void, PDUR_CODE) TpTxConfirmation   (void);
};

/*****************************************************/
/* CONSTS                                            */
/*****************************************************/

/*****************************************************/
/* PARAMS                                            */
/*****************************************************/

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
extern class_PduR PduR;

/*****************************************************/
/* EOF                                               */
/*****************************************************/
