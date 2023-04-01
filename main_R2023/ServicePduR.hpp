#pragma once
/******************************************************************************/
/* File   : ServicePduR.hpp                                                   */
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
#include "infServicePduR_ServiceNvM_Types.hpp"
#include "CfgServicePduR.hpp"
#include "ServicePduR_core.hpp"
#include "infServicePduR_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_ServicePduR:
      INTERFACES_EXPORTED_SERVICEPDUR
      public abstract_module
   ,  public class_ServicePduR_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstModule_TypeAbstract* lptrNvMBlocksRom = (ConstModule_TypeAbstract*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, SERVICEPDUR_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, SERVICEPDUR_CONST,       SERVICEPDUR_APPL_CONST) lptrNvMBlocksRomModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEPDUR_CONFIG_DATA, SERVICEPDUR_APPL_CONST) lptrCfgModule
      );
      FUNC(void, SERVICEPDUR_CODE) DeInitFunction (void);
      FUNC(void, SERVICEPDUR_CODE) MainFunction   (void);
      SERVICEPDUR_CORE_FUNCTIONALITIES
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR(module_ServicePduR, SERVICEPDUR_VAR) ServicePduR;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

