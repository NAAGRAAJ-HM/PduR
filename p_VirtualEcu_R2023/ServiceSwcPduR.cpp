/******************************************************************************/
/* File   : ServiceSwcPduR.cpp                                                */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "ServiceSwcPduR.hpp"

#include "infServiceSwcPduRServiceSwcEcuM.hpp"
#include "infServiceSwcPduREcuabCanIf.hpp"
#include "infServiceSwcPduRServiceSwcCanTp.hpp"

#include "infServiceSwcDcmServiceSwcPduR.hpp"

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcEcuM_InitFunction   (const CfgServiceSwcPduR_Type* CfgServiceSwcPduR_ptr){UNUSED(CfgServiceSwcPduR_ptr);}
FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcEcuM_DeInitFunction (void){}
FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcSchM_MainFunction   (void){}

FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduREcuabCanIf_RxIndication(uint8 lu8IndexBufferRx){
   UNUSED(lu8IndexBufferRx);
}

FUNC(teStatusRequestBuffer, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcCanTp_StartOfReception(uint8 lu8IndexBufferRx){
   //TBD: decision based on Pdu information at PduR
   return infServiceSwcDcmServiceSwcPduR_StartOfReception(lu8IndexBufferRx);
}

FUNC(teStatusRequestBuffer, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcCanTp_CopyRxData(uint8 lu8IndexBufferRx){
   UNUSED(lu8IndexBufferRx);
   return teStatusRequestBuffer_OK;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

