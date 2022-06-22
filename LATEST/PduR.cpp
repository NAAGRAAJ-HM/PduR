/******************************************************************************/
/* File   : PduR.cpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "CfgPduR.hpp"
#include "PduR_core.hpp"
#include "infPduR_Exp.hpp"
#include "infPduR_Imp.hpp"

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
      INTERFACES_EXPORTED_PDUR
      public abstract_module
   ,  public class_PduR_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
            Std_TypeReturn          IsInitDone{E_NOT_OK};
      const CfgModule_TypeAbstract* lptrCfg{(CfgModule_TypeAbstract*)NULL_PTR};

   public:
      module_PduR(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, PDUR_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, PDUR_CONFIG_DATA, PDUR_APPL_CONST) lptrCfgModule
      );
      FUNC(void, PDUR_CODE) DeInitFunction (void);
      FUNC(void, PDUR_CODE) MainFunction   (void);
      PDUR_CORE_FUNCTIONALITIES
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
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         if(STD_HIGH){
            lptrCfg = lptrCfgModule;
         }
         else{
            lptrCfg = &PBcfgPduR;
         }
      }
      else{
#if(STD_ON == PduR_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
      //TBD: Initialize routing path groups based on "Init on start" configuration parameter
#if(STD_ON == PduR_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  PDUR_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, PDUR_CODE) module_PduR::DeInitFunction(void){
#if(STD_ON == PduR_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == PduR_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  PDUR_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, PDUR_CODE) module_PduR::MainFunction(void){
#if(STD_ON == PduR_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == PduR_InitCheck)
   }
   else{
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  PDUR_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(uint16, PDUR_CODE) module_PduR::GetConfigurationId(void){
   CfgPduR_Type* lptrCfgPduR = ((CfgPduR_Type*)lptrCfg);
   return lptrCfgPduR->Core.Id;
}

FUNC(void, PDUR_CODE) module_PduR::DisableRouting(
   TypeIdRoutingPathGroup IdRoutingPathGroup 
){
   if(
      //TBD: RoutingPathGroup with Id exists
      STD_HIGH
   ){
      IdRoutingPathGroup++; //TBD: enable TypeIdRoutingPathGroup 
   }
   else{
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  PDUR_E_ROUTING_PATH_GROUP_ID_INVALID
      );
#endif
   }
}

FUNC(void, PDUR_CODE) module_PduR::EnableRouting(
   TypeIdRoutingPathGroup IdRoutingPathGroup 
){
   if(
      //TBD: RoutingPathGroup with Id exists
      STD_HIGH
   ){
      IdRoutingPathGroup++; //TBD: enable TypeIdRoutingPathGroup 
   }
   else{
#if(STD_ON == PduR_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  PDUR_E_ROUTING_PATH_GROUP_ID_INVALID
      );
#endif
   }
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::Transmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
   gptrinfCanIf_PduR->Transmit();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::TriggerTransmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::TxConfirmation(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
   gptrinfCanIf_PduR->TxConfirmation();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::CancelTransmit(
   TypeIdPdu IdPduTx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::RxIndication(
            TypeIdPdu    IdPduRx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduRx);
   UNUSED(ptrInfoPdu);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::CancelReceive(
   TypeIdPdu IdPduRx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduRx);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::CopyRxData(
   void
){
#if(STD_ON == _ReSIM)
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::CopyTxData(
   void
){
#if(STD_ON == _ReSIM)
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Up::StartOfReception(
   void
){
#if(STD_ON == _ReSIM)
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::Transmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
   gptrinfDcm_PduR->RxIndication();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::TriggerTransmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::TxConfirmation(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
   gptrinfDcm_PduR->TxConfirmation();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::CancelTransmit(
   TypeIdPdu IdPduTx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::RxIndication(
            TypeIdPdu    IdPduRx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduRx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
   gptrinfDcm_PduR->RxIndication();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::CancelReceive(
   TypeIdPdu IdPduRx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduRx);
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::CopyRxData(
   void
){
#if(STD_ON == _ReSIM)
   gptrinfDcm_PduR->CopyRxData();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::CopyTxData(
   void
){
#if(STD_ON == _ReSIM)
   gptrinfDcm_PduR->CopyTxData();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, PDUR_CODE) infPduRClient_Lo::StartOfReception(
   void
){
#if(STD_ON == _ReSIM)
   gptrinfDcm_PduR->StartOfReception();
#else
#endif
   return E_OK;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

