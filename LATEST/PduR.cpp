/******************************************************************************/
/* File   : PduR.cpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "infPduR_EcuM.hpp"
#include "infPduR_Dcm.hpp"
#include "infPduR_SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define PDUR_AR_RELEASE_VERSION_MAJOR                                          4
#define PDUR_AR_RELEASE_VERSION_MINOR                                          3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(PDUR_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible PDUR_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(PDUR_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible PDUR_AR_RELEASE_VERSION_MINOR!"
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
      FUNC(void, PDUR_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, PDUR_CONFIG_DATA, PDUR_APPL_CONST) lptrCfgModule
      );
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
         PDUR_AR_RELEASE_VERSION_MAJOR
      ,  PDUR_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, PDUR_CODE) module_PduR::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, PDUR_CONFIG_DATA, PDUR_APPL_CONST) lptrCfgModule
){
#if(STD_ON == PduR_InitCheck)
   if(E_OK == IsInitDone){
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
      if(NULL_PTR == lptrCfgModule){
#if(STD_ON == PduR_DevErrorDetect)
         Det_ReportError(
         );
#endif
      }
      else{
         if(STD_LOW){
// check lptrCfgModule for memory faults
            lptrCfg = lptrCfgModule;
         }
         else{
// use PBcfg_CanIf as back-up configuration
            lptrCfg = PBcfg_CanIf;
         }
      }
      IsInitDone = E_OK;
#if(STD_ON == PduR_InitCheck)
   }
#endif
}

FUNC(void, PDUR_CODE) module_PduR::DeInitFunction(void){
#if(STD_ON == PduR_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
      IsInitDone = E_NOT_OK;
#if(STD_ON == PduR_InitCheck)
   }
#endif
}

FUNC(void, PDUR_CODE) module_PduR::MainFunction(void){
#if(STD_ON == PduR_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
#if(STD_ON == PduR_InitCheck)
   }
#endif
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

