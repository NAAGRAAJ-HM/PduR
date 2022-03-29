/******************************************************************************/
/* File   : PduR.cpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.hpp"
#include "infPduR_EcuM.hpp"
#include "infPduR_Dcm.hpp"
#include "infPduR_SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define PDUR_AR_RELEASE_MAJOR_VERSION                                          4
#define PDUR_AR_RELEASE_MINOR_VERSION                                          3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(PDUR_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION)
   #error "Incompatible PDUR_AR_RELEASE_MAJOR_VERSION!"
#endif

#if(PDUR_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)
   #error "Incompatible PDUR_AR_RELEASE_MINOR_VERSION!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_PduR:
      public abstract_module
{
   public:
      module_PduR(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, PDUR_CODE) InitFunction   (void);
      FUNC(void, PDUR_CODE) DeInitFunction (void);
      FUNC(void, PDUR_CODE) MainFunction   (void);
};

extern VAR(module_PduR, PDUR_VAR) PduR;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, PDUR_VAR, PDUR_CONST) gptrinfEcuMClient_PduR = &PduR;
CONSTP2VAR(infDcmClient,  PDUR_VAR, PDUR_CONST) gptrinfDcmClient_PduR  = &PduR;
CONSTP2VAR(infSchMClient, PDUR_VAR, PDUR_CONST) gptrinfSchMClient_PduR = &PduR;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
#include "CfgPduR.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_PduR, PDUR_VAR) PduR(
   {
         0x0000
      ,  0xFFFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, PDUR_CODE) module_PduR::InitFunction(void){
   PduR.IsInitDone = E_OK;
}

FUNC(void, PDUR_CODE) module_PduR::DeInitFunction(void){
   PduR.IsInitDone = E_NOT_OK;
}

FUNC(void, PDUR_CODE) module_PduR::MainFunction(void){
}

class class_PduR_Unused{
   public:
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

