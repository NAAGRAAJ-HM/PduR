/******************************************************************************/
/* File   : ServicePduR.cpp                                                   */
/*                                                                            */
/* Author : Nagaraja HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Nagaraja HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/NagarajaHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "ServicePduR.hpp"
#include "infServicePduR_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_ServicePduR, SERVICEPDUR_VAR) ServicePduR;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SERVICEPDUR_CODE) module_ServicePduR::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, SERVICEPDUR_CONST,       SERVICEPDUR_APPL_CONST) lptrNvMBlocksRomModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEPDUR_CONFIG_DATA, SERVICEPDUR_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServicePduR_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrNvMBlocksRomModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrNvMBlocksRom = lptrNvMBlocksRomModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == ServicePduR_DevErrorDetect)
         ServiceDet_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
      //TBD: Initialize routing path groups based on "Init on start" configuration parameter
#if(STD_ON == ServicePduR_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == ServicePduR_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEPDUR_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEPDUR_CODE) module_ServicePduR::DeInitFunction(
   void
){
#if(STD_ON == ServicePduR_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServicePduR_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == ServicePduR_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEPDUR_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEPDUR_CODE) module_ServicePduR::MainFunction(
   void
){
#if(STD_ON == ServicePduR_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServicePduR_InitCheck)
   }
   else{
#if(STD_ON == ServicePduR_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEPDUR_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(uint16, SERVICEPDUR_CODE) module_ServicePduR::GetConfigurationId(
   void
){
   NvM_BlocksNv_ServicePduR_Type* lptrNvM_BlocksNv_ServicePduR = ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg);
   return lptrNvM_BlocksNv_ServicePduR->Core.Id;
}

FUNC(void, SERVICEPDUR_CODE) module_ServicePduR::DisableRouting(
   TypeIdRoutingPathGroup IdRoutingPathGroup 
){
   if(
      //TBD: RoutingPathGroup with Id exists
      STD_HIGH
   ){
      IdRoutingPathGroup++; //TBD: enable TypeIdRoutingPathGroup 
   }
   else{
#if(STD_ON == ServicePduR_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEPDUR_E_ROUTING_PATH_GROUP_ID_INVALID
      );
#endif
   }
}

FUNC(void, SERVICEPDUR_CODE) module_ServicePduR::EnableRouting(
   TypeIdRoutingPathGroup IdRoutingPathGroup 
){
   if(
      //TBD: RoutingPathGroup with Id exists
      STD_HIGH
   ){
      IdRoutingPathGroup++; //TBD: enable TypeIdRoutingPathGroup 
   }
   else{
#if(STD_ON == ServicePduR_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEPDUR_E_ROUTING_PATH_GROUP_ID_INVALID
      );
#endif
   }
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::Transmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfEcuabCanIf_ServicePduR->Transmit();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::TriggerTransmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::TxConfirmation(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfEcuabCanIf_ServicePduR->TxConfirmation();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::McalCancelTransmit(
   TypeIdPdu IdPduTx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::RxIndication(
            TypeIdPdu    IdServicePduRx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdServicePduRx);
   UNUSED(ptrInfoPdu);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::McalCancelReceive(
   TypeIdPdu IdServicePduRx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdServicePduRx);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::CopyRxData(
   void
){
#if(STD_ON == _ReSIM)
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::CopyTxData(
   void
){
#if(STD_ON == _ReSIM)
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Up::StartOfReception(
   void
){
#if(STD_ON == _ReSIM)
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::Transmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfServiceDcm_ServicePduR->RxIndication();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::TriggerTransmit(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::TxConfirmation(
            TypeIdPdu    IdPduTx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfServiceDcm_ServicePduR->TxConfirmation();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::McalCancelTransmit(
   TypeIdPdu IdPduTx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdPduTx);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::RxIndication(
            TypeIdPdu    IdServicePduRx
   ,  const TypeInfoPdu* ptrInfoPdu
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdServicePduRx);
   UNUSED(ptrInfoPdu);
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfServiceDcm_ServicePduR->RxIndication();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::McalCancelReceive(
   TypeIdPdu IdServicePduRx
){
   //TBD: re-entrant for different Id, non-reentrant for same Id
   UNUSED(IdServicePduRx);
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::CopyRxData(
   void
){
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfServiceDcm_ServicePduR->CopyRxData();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::CopyTxData(
   void
){
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfServiceDcm_ServicePduR->CopyTxData();
#else
#endif
   return E_OK;
}

FUNC(Std_TypeReturn, SERVICEPDUR_CODE) infServicePduRClient_Lo::StartOfReception(
   void
){
#if(STD_ON == _ReSIM)
// ((NvM_BlocksNv_ServicePduR_Type*)lptrCfg)->ptrinfServiceDcm_ServicePduR->StartOfReception();
#else
#endif
   return E_OK;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

