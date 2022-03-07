/*****************************************************/
/* File   : PduR.cpp                                 */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "module.h"
#include "PduR_EcuM.h"
#include "PduR_SchM.h"
#include "PduR_Unused.h"

/*****************************************************/
/* #DEFINES                                          */
/*****************************************************/

/*****************************************************/
/* MACROS                                            */
/*****************************************************/

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
class module_PduR:
      public abstract_module
{
   public:
      FUNC(void, PDUR_CODE) InitFunction   (void);
      FUNC(void, PDUR_CODE) DeInitFunction (void);
      FUNC(void, PDUR_CODE) MainFunction   (void);
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
module_PduR    PduR;
infEcuMClient* gptrinfEcuMClient_PduR = &PduR;
infSchMClient* gptrinfSchMClient_PduR = &PduR;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, PDUR_CODE) module_PduR::InitFunction(void){
}

FUNC(void, PDUR_CODE) module_PduR::DeInitFunction(void){
}

FUNC(void, PDUR_CODE) module_PduR::MainFunction(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::GetVersinInfo(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::GetConfigurationId(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::DisableRouting(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::EnableRouting(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::Transmit(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::CancelTransmit(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::CancelReceive(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::RxIndication(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TxConfirmation(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TriggerTrasnmit(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TpCopyRxData(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TpRxIndication(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TpStartOfReception(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TpCopyTxData(void){
}

FUNC(void, PDUR_CODE) class_PduR_Unused::TpTxConfirmation(void){
}

/*****************************************************/
/* EOF                                               */
/*****************************************************/

