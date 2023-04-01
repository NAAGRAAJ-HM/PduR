#pragma once
/******************************************************************************/
/* File   : infServicePduRClient_Up.hpp                                              */
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
#include "CompilerCfg_ServicePduR.hpp"
#include "ComStackTypes.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class infServicePduRClient_Up{
   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) Transmit(
                  TypeIdPdu    IdPduTx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) TriggerTransmit(
                  TypeIdPdu    IdPduTx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) TxConfirmation(
                  TypeIdPdu    IdPduTx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) RxIndication(
                  TypeIdPdu    IdServicePduRx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) McalCancelTransmit(
         TypeIdPdu IdServicePduRx
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) McalCancelReceive(
         TypeIdPdu IdServicePduRx
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) CopyRxData(
         void
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) CopyTxData(
         void
      );

      FUNC(Std_TypeReturn, SERVICEPDUR_CODE) StartOfReception(
         void
      );
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

