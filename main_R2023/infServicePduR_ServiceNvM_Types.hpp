#pragma once
/******************************************************************************/
/* File   : infServicePduR_ServiceNvM_Types.hpp                               */
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
/* TYPEDEFS                                                                   */
/******************************************************************************/
class NvM_BlocksRom_ServicePduR_Type:
      public ConstModule_TypeAbstract
{
};

typedef struct{
   uint32 bUpperModule            :1;
   uint32 bLowerModule            :1;
   uint32 bCommunicationInterface :1;
   uint32 bTransportProtocol      :1;
   uint32 bTransmit               :1;
   uint32 bTransmitTp             :1;
   uint32 bTxConfirmation         :1;
   uint32 bTxConfirmationTp       :1;
   uint32 bRxIndication           :1;
   uint32 bRxIndicationTp         :1;
   uint32 bCancelTransmit         :1;
   uint32 bCancelReceive          :1;
   uint32 bCopyTxData             :1;
   uint32 bCopyRxData             :1;
   uint32 bTriggerTransmit        :1;
   uint32 bReTransmition          :1;
   uint32 bStartOfReception       :1;
   uint32 bUseTag                 :1;
}TypeClient;

typedef void TypePdu;     //TBD: Real implementation

typedef uint16 TypeIdRoutingPathGroup;

typedef struct{
   TypePdu *ptrSrc;
   TypePdu *ptrDst;
}TypeRoutingPath;

typedef struct{
   TypeIdRoutingPathGroup Id;
   uint16                 u16CntMaxRoutingPath;
   TypeRoutingPath        astGroup[1];
}TypeRoutingPathGroup;

class Type_NvM_BlocksNv_ServicePduRCore{
   public:
      uint16                Id;
      TypeClient*           aptrClients[1];
      uint16                u16CntMaxRoutingPathGroup;
      TypeRoutingPathGroup* aptrGroups[1];
};

class NvM_BlocksNv_ServicePduR_Type:
      public CfgModule_TypeAbstract
{
   public:
      Type_NvM_BlocksNv_ServicePduRCore Core;
};

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

