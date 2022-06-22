#pragma once
/******************************************************************************/
/* File   : infPduRClient_Lo.hpp                                              */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_PduR.hpp"
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
class infPduRClient_Lo{
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
                  TypeIdPdu    IdPduRx
         ,  const TypeInfoPdu* ptrInfoPdu
      );

      FUNC(Std_TypeReturn, PDUR_CODE) CancelTransmit(
         TypeIdPdu IdPduRx
      );

      FUNC(Std_TypeReturn, PDUR_CODE) CancelReceive(
         TypeIdPdu IdPduRx
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

