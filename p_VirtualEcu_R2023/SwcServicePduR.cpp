/******************************************************************************/
/* File   : SwcServicePduR.cpp                                                */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "SwcServicePduR.hpp"

#include "infSwcServicePduRSwcServiceEcuM.hpp"
#include "infSwcServicePduREcuabCanIf.hpp"
#include "infSwcServicePduRSwcServiceCanTp.hpp"

#include "infSwcServiceDcmSwcServicePduR.hpp"

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
FUNC(void, SWCSERVICEPDUR_CODE) infSwcServicePduRSwcServiceEcuM_InitFunction   (const CfgSwcServicePduR_tst* CfgSwcServicePduR_ptr){UNUSED(CfgSwcServicePduR_ptr);}
FUNC(void, SWCSERVICEPDUR_CODE) infSwcServicePduRSwcServiceEcuM_DeInitFunction (void){}
FUNC(void, SWCSERVICEPDUR_CODE) infSwcServicePduRSwcServiceSchM_MainFunction   (void){}

FUNC(void, SWCSERVICEPDUR_CODE) infSwcServicePduREcuabCanIf_RxIndication(uint8 lu8IndexBufferRx){
   UNUSED(lu8IndexBufferRx);
}

FUNC(void, SWCSERVICEPDUR_CODE) infSwcServicePduRSwcServiceCanTp_RxIndication(uint8 lu8IndexBufferRx){
   infSwcServiceDcmSwcServicePduR_RxIndication(lu8IndexBufferRx); //TBD: In this project, only Dcm is indirect client of CanTp
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

