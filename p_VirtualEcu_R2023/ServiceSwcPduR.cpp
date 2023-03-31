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
FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcEcuM_InitFunction   (const CfgServiceSwcPduR_tst* CfgServiceSwcPduR_ptr){UNUSED(CfgServiceSwcPduR_ptr);}
FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcEcuM_DeInitFunction (void){}
FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcSchM_MainFunction   (void){}

FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduREcuabCanIf_RxIndication(uint8 lu8IndexBufferRx){
   UNUSED(lu8IndexBufferRx);
}

FUNC(void, SERVICESWCPDUR_CODE) infServiceSwcPduRServiceSwcCanTp_RxIndication(uint8 lu8IndexBufferRx){
   infServiceSwcDcmServiceSwcPduR_RxIndication(lu8IndexBufferRx); //TBD: In this project, only Dcm is indirect client of CanTp
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

