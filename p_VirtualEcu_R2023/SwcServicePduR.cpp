/******************************************************************************/
/* File   : SwcServicePduR.cpp                                                */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
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

