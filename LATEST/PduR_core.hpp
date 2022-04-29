#pragma once
/******************************************************************************/
/* File   : PduR_core.hpp                                                     */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_PduR.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define PDUR_CORE_FUNCTIONALITIES                                              \
              FUNC(void, PDUR_CODE) GetConfigurationId (void);                 \
              FUNC(void, PDUR_CODE) DisableRouting     (void);                 \
              FUNC(void, PDUR_CODE) EnableRouting      (void);                 \
              FUNC(void, PDUR_CODE) Transmit           (void);                 \
              FUNC(void, PDUR_CODE) CancelTransmit     (void);                 \
              FUNC(void, PDUR_CODE) CancelReceive      (void);                 \
              FUNC(void, PDUR_CODE) RxIndication       (void);                 \
              FUNC(void, PDUR_CODE) TxConfirmation     (void);                 \
              FUNC(void, PDUR_CODE) TriggerTrasnmit    (void);                 \
              FUNC(void, PDUR_CODE) TpCopyRxData       (void);                 \
              FUNC(void, PDUR_CODE) TpRxIndication     (void);                 \
              FUNC(void, PDUR_CODE) TpStartOfReception (void);                 \
              FUNC(void, PDUR_CODE) TpCopyTxData       (void);                 \
              FUNC(void, PDUR_CODE) TpTxConfirmation   (void);                 \

#define PDUR_CORE_FUNCTIONALITIES_VIRTUAL                                      \
      virtual FUNC(void, PDUR_CODE) GetConfigurationId (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) DisableRouting     (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) EnableRouting      (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) Transmit           (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) CancelTransmit     (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) CancelReceive      (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) RxIndication       (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TxConfirmation     (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TriggerTrasnmit    (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TpCopyRxData       (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TpRxIndication     (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TpStartOfReception (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TpCopyTxData       (void) = 0;             \
      virtual FUNC(void, PDUR_CODE) TpTxConfirmation   (void) = 0;             \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_PduR_Functionality{
   public:
      PDUR_CORE_FUNCTIONALITIES_VIRTUAL
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
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

