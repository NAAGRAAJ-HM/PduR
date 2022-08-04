#pragma once
/******************************************************************************/
/* File   : infServicePduRClient_Up.hpp                                              */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
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
      FUNC(Std_TypeReturn, PDUR_CODE) Transmit(
                  TypeIdPdu    IdPduTx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, PDUR_CODE) TriggerTransmit(
                  TypeIdPdu    IdPduTx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, PDUR_CODE) TxConfirmation(
                  TypeIdPdu    IdPduTx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, PDUR_CODE) RxIndication(
                  TypeIdPdu    IdServicePduRx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, PDUR_CODE) McalCancelTransmit(
         TypeIdPdu IdServicePduRx
      );

      FUNC(Std_TypeReturn, PDUR_CODE) McalCancelReceive(
         TypeIdPdu IdServicePduRx
      );

      FUNC(Std_TypeReturn, PDUR_CODE) CopyRxData(
         void
      );

      FUNC(Std_TypeReturn, PDUR_CODE) CopyTxData(
         void
      );

      FUNC(Std_TypeReturn, PDUR_CODE) StartOfReception(
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

