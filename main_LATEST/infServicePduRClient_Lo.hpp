#pragma once
/******************************************************************************/
/* File   : infServicePduRClient_Lo.hpp                                              */
/* Author : Nagaraja HULIYAPURADA-MATA                                        */
/* Date   : 01.02.1982                                                        */
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
class infServicePduRClient_Lo{
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

