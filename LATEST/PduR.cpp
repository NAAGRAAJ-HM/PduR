/*****************************************************/
/* File   : PduR.cpp                                 */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "PduR.h"

#include "PduR_EcuM.h"
#include "PduR_SchM.h"

/*****************************************************/
/* #DEFINES                                          */
/*****************************************************/

/*****************************************************/

/*****************************************************/
/* MACROS                                            */
/*****************************************************/

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/

/*****************************************************/
/* CONSTS                                            */
/*****************************************************/

/*****************************************************/
/* PARAMS                                            */
/*****************************************************/

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
class_PduR_EcuM_Init PduR_EcuM_Init;
class_PduR_SchM_Main PduR_SchM_Main;
class_PduR PduR;

class_EcuM_Init_Client *EcuM_Init_Client_ptr_PduR = &PduR_EcuM_Init;
class_SchM_Main_Client *SchM_Main_Client_ptr_PduR = &PduR_SchM_Main;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, PDUR_CODE) class_PduR_EcuM_Init::InitFunction(void){
}

FUNC(void, PDUR_CODE) class_PduR_SchM_Main::MainFunction(void){
}

FUNC(void, PDUR_CODE) class_PduR::GetVersinInfo(void){
}

FUNC(void, PDUR_CODE) class_PduR::GetConfigurationId(void){
}

FUNC(void, PDUR_CODE) class_PduR::DisableRouting(void){
}

FUNC(void, PDUR_CODE) class_PduR::EnableRouting(void){
}

FUNC(void, PDUR_CODE) class_PduR::Transmit(void){
}

FUNC(void, PDUR_CODE) class_PduR::CancelTransmit(void){
}

FUNC(void, PDUR_CODE) class_PduR::CancelReceive(void){
}

FUNC(void, PDUR_CODE) class_PduR::RxIndication(void){
}

FUNC(void, PDUR_CODE) class_PduR::TxConfirmation(void){
}

FUNC(void, PDUR_CODE) class_PduR::TriggerTrasnmit(void){
}

FUNC(void, PDUR_CODE) class_PduR::TpCopyRxData(void){
}

FUNC(void, PDUR_CODE) class_PduR::TpRxIndication(void){
}

FUNC(void, PDUR_CODE) class_PduR::TpStartOfReception(void){
}

FUNC(void, PDUR_CODE) class_PduR::TpCopyTxData(void){
}

FUNC(void, PDUR_CODE) class_PduR::TpTxConfirmation(void){
}

/*****************************************************/
/* EOF                                               */
/*****************************************************/

