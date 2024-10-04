/*
 * dp83826e.h
 *
 *  Created on: 08.05.2023
 *      Author: sven.bergmann
 */

#ifndef INC_DP83826E_H_

#define INC_DP83826E_H_



#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


#define DP83826E_BCR      				((uint16_t)0x0000U)
#define DP83826E_BCR_SOFT_RESET         ((uint16_t)0x8000U)


#define DP83826E_BSR     				((uint16_t)0x0001U)
#define DP83826E_BSR_100BASE_T4       	((uint16_t)0x8000U)
#define DP83826E_BSR_100BASE_TX_FD    	((uint16_t)0x4000U)
#define DP83826E_BSR_100BASE_TX_HD    	((uint16_t)0x2000U)
#define DP83826E_BSR_10BASE_T_FD      	((uint16_t)0x1000U)
#define DP83826E_BSR_10BASE_T_HD      	((uint16_t)0x0800U)
#define DP83826E_BSR_100BASE_T2_FD    	((uint16_t)0x0400U)
#define DP83826E_BSR_100BASE_T2_HD    	((uint16_t)0x0200U)
#define DP83826E_BSR_EXTENDED_STATUS  	((uint16_t)0x0100U)
#define DP83826E_BSR_AUTONEGO_CPLT    	((uint16_t)0x0020U)
#define DP83826E_BSR_REMOTE_FAULT     	((uint16_t)0x0010U)
#define DP83826E_BSR_AUTONEGO_ABILITY 	((uint16_t)0x0008U)
#define DP83826E_BSR_LINK_STATUS      	((uint16_t)0x0004U)
#define DP83826E_BSR_JABBER_DETECT    	((uint16_t)0x0002U)
#define DP83826E_BSR_EXTENDED_CAP     	((uint16_t)0x0001U)

#define DP83826E_LEDCR					((uint16_t)0x0018U)
#define DP83826E_LEDCR_CONF				((uint16_t)0x0480U)

#define DP83826E_PHYCR      			((uint16_t)0x0019U)
#define DP83826E_PHYCR_PHY_ADDR   		((uint16_t)0x001FU)


#define DP83826E_REGCR					((uint16_t)0x000DU) // Erweiterter Register Zugriff -> 	Extended Register Control Register
#define DP83826E_REGCR_FUN_ADR			((uint16_t)0x001FU)
#define DP83826E_REGCR_FUN_DATA			((uint16_t)0x401FU)
#define DP83826E_ADDAR  				((uint16_t)0x000EU)	// Erweoterte Register Daten ->		Extended Register Data Register

#define DP83826E_LEDCFG2				((uint16_t)0x0469U)
#define DP83826E_LEDCFG2_CONF			((uint16_t)0x0444U)


#define DP83826E_PHYI1R   ((uint16_t)0x0002U)
#define DP83826E_PHYI2R   ((uint16_t)0x0003U)
#define DP83826E_ANAR     ((uint16_t)0x0004U)
#define DP83826E_ANLPAR   ((uint16_t)0x0005U)
#define DP83826E_ANER     ((uint16_t)0x0006U)
#define DP83826E_ANNPTR   ((uint16_t)0x0007U)
#define DP83826E_ANNPRR   ((uint16_t)0x0008U)
//#define DP83826E_MMDACR   ((uint16_t)0x000DU)
//#define DP83826E_MMDAADR  ((uint16_t)0x000EU)
#define DP83826E_ENCTR    ((uint16_t)0x0010U)
#define DP83826E_MCSR     ((uint16_t)0x0011U)
//#define DP83826E_TPDCR    ((uint16_t)0x0018U)
//#define DP83826E_TCSR     ((uint16_t)0x0019U)
#define DP83826E_SECR     ((uint16_t)0x001AU)
#define DP83826E_SCSIR    ((uint16_t)0x001BU)
#define DP83826E_CLR      ((uint16_t)0x001CU)
#define DP83826E_ISFR     ((uint16_t)0x001DU)
#define DP83826E_IMR      ((uint16_t)0x001EU)
#define DP83826E_PHYSCSR  ((uint16_t)0x001FU)
/**
  * @}
  */

/** @defgroup LAN8742_BCR_Bit_Definition LAN8742 BCR Bit Definition
  * @{
  */
#define DP83826E_BCR_LOOPBACK           ((uint16_t)0x4000U)
#define DP83826E_BCR_SPEED_SELECT       ((uint16_t)0x2000U)
#define DP83826E_BCR_AUTONEGO_EN        ((uint16_t)0x1000U)
#define DP83826E_BCR_POWER_DOWN         ((uint16_t)0x0800U)
#define DP83826E_BCR_ISOLATE            ((uint16_t)0x0400U)
#define DP83826E_BCR_RESTART_AUTONEGO   ((uint16_t)0x0200U)
#define DP83826E_BCR_DUPLEX_MODE        ((uint16_t)0x0100U)
/**
  * @}
  */

/** @defgroup LAN8742_BSR_Bit_Definition LAN8742 BSR Bit Definition
  * @{
  */

/**
  * @}
  */

/** @defgroup LAN8742_PHYI1R_Bit_Definition LAN8742 PHYI1R Bit Definition
  * @{
  */
#define DP83826E_PHYI1R_OUI_3_18           ((uint16_t)0xFFFFU)
/**
  * @}
  */

/** @defgroup LAN8742_PHYI2R_Bit_Definition LAN8742 PHYI2R Bit Definition
  * @{
  */
#define DP83826E_PHYI2R_OUI_19_24          ((uint16_t)0xFC00U)
#define DP83826E_PHYI2R_MODEL_NBR          ((uint16_t)0x03F0U)
#define DP83826E_PHYI2R_REVISION_NBR       ((uint16_t)0x000FU)
/**
  * @}
  */

/** @defgroup LAN8742_ANAR_Bit_Definition LAN8742 ANAR Bit Definition
  * @{
  */
#define DP83826E_ANAR_NEXT_PAGE               ((uint16_t)0x8000U)
#define DP83826E_ANAR_REMOTE_FAULT            ((uint16_t)0x2000U)
#define DP83826E_ANAR_PAUSE_OPERATION         ((uint16_t)0x0C00U)
#define DP83826E_ANAR_PO_NOPAUSE              ((uint16_t)0x0000U)
#define DP83826E_ANAR_PO_SYMMETRIC_PAUSE      ((uint16_t)0x0400U)
#define DP83826E_ANAR_PO_ASYMMETRIC_PAUSE     ((uint16_t)0x0800U)
#define DP83826E_ANAR_PO_ADVERTISE_SUPPORT    ((uint16_t)0x0C00U)
#define DP83826E_ANAR_100BASE_TX_FD           ((uint16_t)0x0100U)
#define DP83826E_ANAR_100BASE_TX              ((uint16_t)0x0080U)
#define DP83826E_ANAR_10BASE_T_FD             ((uint16_t)0x0040U)
#define DP83826E_ANAR_10BASE_T                ((uint16_t)0x0020U)
#define DP83826E_ANAR_SELECTOR_FIELD          ((uint16_t)0x000FU)
/**
  * @}
  */

/** @defgroup LAN8742_ANLPAR_Bit_Definition LAN8742 ANLPAR Bit Definition
  * @{
  */
#define DP83826E_ANLPAR_NEXT_PAGE            ((uint16_t)0x8000U)
#define DP83826E_ANLPAR_REMOTE_FAULT         ((uint16_t)0x2000U)
#define DP83826E_ANLPAR_PAUSE_OPERATION      ((uint16_t)0x0C00U)
#define DP83826E_ANLPAR_PO_NOPAUSE           ((uint16_t)0x0000U)
#define DP83826E_ANLPAR_PO_SYMMETRIC_PAUSE   ((uint16_t)0x0400U)
#define DP83826E_ANLPAR_PO_ASYMMETRIC_PAUSE  ((uint16_t)0x0800U)
#define DP83826E_ANLPAR_PO_ADVERTISE_SUPPORT ((uint16_t)0x0C00U)
#define DP83826E_ANLPAR_100BASE_TX_FD        ((uint16_t)0x0100U)
#define DP83826E_ANLPAR_100BASE_TX           ((uint16_t)0x0080U)
#define DP83826E_ANLPAR_10BASE_T_FD          ((uint16_t)0x0040U)
#define DP83826E_ANLPAR_10BASE_T             ((uint16_t)0x0020U)
#define DP83826E_ANLPAR_SELECTOR_FIELD       ((uint16_t)0x000FU)
/**
  * @}
  */

/** @defgroup LAN8742_ANER_Bit_Definition LAN8742 ANER Bit Definition
  * @{
  */
#define DP83826E_ANER_RX_NP_LOCATION_ABLE    ((uint16_t)0x0040U)
#define DP83826E_ANER_RX_NP_STORAGE_LOCATION ((uint16_t)0x0020U)
#define DP83826E_ANER_PARALLEL_DETECT_FAULT  ((uint16_t)0x0010U)
#define DP83826E_ANER_LP_NP_ABLE             ((uint16_t)0x0008U)
#define DP83826E_ANER_NP_ABLE                ((uint16_t)0x0004U)
#define DP83826E_ANER_PAGE_RECEIVED          ((uint16_t)0x0002U)
#define DP83826E_ANER_LP_AUTONEG_ABLE        ((uint16_t)0x0001U)
/**
  * @}
  */

/** @defgroup LAN8742_ANNPTR_Bit_Definition LAN8742 ANNPTR Bit Definition
  * @{
  */
#define DP83826E_ANNPTR_NEXT_PAGE         ((uint16_t)0x8000U)
#define DP83826E_ANNPTR_MESSAGE_PAGE      ((uint16_t)0x2000U)
#define DP83826E_ANNPTR_ACK2              ((uint16_t)0x1000U)
#define DP83826E_ANNPTR_TOGGLE            ((uint16_t)0x0800U)
#define DP83826E_ANNPTR_MESSAGGE_CODE     ((uint16_t)0x07FFU)
/**
  * @}
  */

/** @defgroup LAN8742_ANNPRR_Bit_Definition LAN8742 ANNPRR Bit Definition
  * @{
  */
#define DP83826E_ANNPTR_NEXT_PAGE         ((uint16_t)0x8000U)
#define DP83826E_ANNPRR_ACK               ((uint16_t)0x4000U)
#define DP83826E_ANNPRR_MESSAGE_PAGE      ((uint16_t)0x2000U)
#define DP83826E_ANNPRR_ACK2              ((uint16_t)0x1000U)
#define DP83826E_ANNPRR_TOGGLE            ((uint16_t)0x0800U)
#define DP83826E_ANNPRR_MESSAGGE_CODE     ((uint16_t)0x07FFU)
/**
  * @}
  */

/** @defgroup LAN8742_MMDACR_Bit_Definition LAN8742 MMDACR Bit Definition
  * @{
  */
#define DP83826E_MMDACR_MMD_FUNCTION       ((uint16_t)0xC000U)
#define DP83826E_MMDACR_MMD_FUNCTION_ADDR  ((uint16_t)0x0000U)
#define DP83826E_MMDACR_MMD_FUNCTION_DATA  ((uint16_t)0x4000U)
#define DP83826E_MMDACR_MMD_DEV_ADDR       ((uint16_t)0x001FU)
/**
  * @}
  */

/** @defgroup LAN8742_ENCTR_Bit_Definition LAN8742 ENCTR Bit Definition
  * @{
  */
#define DP83826E_ENCTR_TX_ENABLE             ((uint16_t)0x8000U)
#define DP83826E_ENCTR_TX_TIMER              ((uint16_t)0x6000U)
#define DP83826E_ENCTR_TX_TIMER_1S           ((uint16_t)0x0000U)
#define DP83826E_ENCTR_TX_TIMER_768MS        ((uint16_t)0x2000U)
#define DP83826E_ENCTR_TX_TIMER_512MS        ((uint16_t)0x4000U)
#define DP83826E_ENCTR_TX_TIMER_265MS        ((uint16_t)0x6000U)
#define DP83826E_ENCTR_RX_ENABLE             ((uint16_t)0x1000U)
#define DP83826E_ENCTR_RX_MAX_INTERVAL       ((uint16_t)0x0C00U)
#define DP83826E_ENCTR_RX_MAX_INTERVAL_64MS  ((uint16_t)0x0000U)
#define DP83826E_ENCTR_RX_MAX_INTERVAL_256MS ((uint16_t)0x0400U)
#define DP83826E_ENCTR_RX_MAX_INTERVAL_512MS ((uint16_t)0x0800U)
#define DP83826E_ENCTR_RX_MAX_INTERVAL_1S    ((uint16_t)0x0C00U)
#define DP83826E_ENCTR_EX_CROSS_OVER         ((uint16_t)0x0002U)
#define DP83826E_ENCTR_EX_MANUAL_CROSS_OVER  ((uint16_t)0x0001U)
/**
  * @}
  */

/** @defgroup LAN8742_MCSR_Bit_Definition LAN8742 MCSR Bit Definition
  * @{
  */
#define DP83826E_MCSR_EDPWRDOWN        ((uint16_t)0x2000U)
#define DP83826E_MCSR_FARLOOPBACK      ((uint16_t)0x0200U)
#define DP83826E_MCSR_ALTINT           ((uint16_t)0x0040U)
#define DP83826E_MCSR_ENERGYON         ((uint16_t)0x0002U)
/**
  * @}
  */

/** @defgroup LAN8742_SMR_Bit_Definition LAN8742 SMR Bit Definition
  * @{
  */
//#define DP83826E_SMR_MODE       ((uint16_t)0x00E0U)
/**
  * @}
  */

/** @defgroup LAN8742_TPDCR_Bit_Definition LAN8742 TPDCR Bit Definition
  * @{
  */
#define DP83826E_TPDCR_DELAY_IN                 ((uint16_t)0x8000U)
#define DP83826E_TPDCR_LINE_BREAK_COUNTER       ((uint16_t)0x7000U)
#define DP83826E_TPDCR_PATTERN_HIGH             ((uint16_t)0x0FC0U)
#define DP83826E_TPDCR_PATTERN_LOW              ((uint16_t)0x003FU)
/**
  * @}
  */

/** @defgroup LAN8742_TCSR_Bit_Definition LAN8742 TCSR Bit Definition
  * @{
  */
#define DP83826E_TCSR_TDR_ENABLE           ((uint16_t)0x8000U)
#define DP83826E_TCSR_TDR_AD_FILTER_ENABLE ((uint16_t)0x4000U)
#define DP83826E_TCSR_TDR_CH_CABLE_TYPE    ((uint16_t)0x0600U)
#define DP83826E_TCSR_TDR_CH_CABLE_DEFAULT ((uint16_t)0x0000U)
#define DP83826E_TCSR_TDR_CH_CABLE_SHORTED ((uint16_t)0x0200U)
#define DP83826E_TCSR_TDR_CH_CABLE_OPEN    ((uint16_t)0x0400U)
#define DP83826E_TCSR_TDR_CH_CABLE_MATCH   ((uint16_t)0x0600U)
#define DP83826E_TCSR_TDR_CH_STATUS        ((uint16_t)0x0100U)
#define DP83826E_TCSR_TDR_CH_LENGTH        ((uint16_t)0x00FFU)
/**
  * @}
  */

/** @defgroup LAN8742_SCSIR_Bit_Definition LAN8742 SCSIR Bit Definition
  * @{
  */
#define DP83826E_SCSIR_AUTO_MDIX_ENABLE    ((uint16_t)0x8000U)
#define DP83826E_SCSIR_CHANNEL_SELECT      ((uint16_t)0x2000U)
#define DP83826E_SCSIR_SQE_DISABLE         ((uint16_t)0x0800U)
#define DP83826E_SCSIR_XPOLALITY           ((uint16_t)0x0010U)
/**
  * @}
  */

/** @defgroup LAN8742_CLR_Bit_Definition LAN8742 CLR Bit Definition
  * @{
  */
#define DP83826E_CLR_CABLE_LENGTH       ((uint16_t)0xF000U)
/**
  * @}
  */

/** @defgroup LAN8742_IMR_ISFR_Bit_Definition LAN8742 IMR ISFR Bit Definition
  * @{
  */
#define DP83826E_INT_8       ((uint16_t)0x0100U)
#define DP83826E_INT_7       ((uint16_t)0x0080U)
#define DP83826E_INT_6       ((uint16_t)0x0040U)
#define DP83826E_INT_5       ((uint16_t)0x0020U)
#define DP83826E_INT_4       ((uint16_t)0x0010U)
#define DP83826E_INT_3       ((uint16_t)0x0008U)
#define DP83826E_INT_2       ((uint16_t)0x0004U)
#define DP83826E_INT_1       ((uint16_t)0x0002U)
/**
  * @}
  */

/** @defgroup LAN8742_PHYSCSR_Bit_Definition LAN8742 PHYSCSR Bit Definition
  * @{
  */
#define DP83826E_PHYSCSR_AUTONEGO_DONE   ((uint16_t)0x1000U)
#define DP83826E_PHYSCSR_HCDSPEEDMASK    ((uint16_t)0x001CU)
#define DP83826E_PHYSCSR_10BT_HD         ((uint16_t)0x0004U)
#define DP83826E_PHYSCSR_10BT_FD         ((uint16_t)0x0014U)
#define DP83826E_PHYSCSR_100BTX_HD       ((uint16_t)0x0008U)
#define DP83826E_PHYSCSR_100BTX_FD       ((uint16_t)0x0018U)
/**
  * @}
  */

/** @defgroup LAN8742_Status LAN8742 Status
  * @{
  */

#define  DP83826E_STATUS_READ_ERROR            ((int32_t)-5)
#define  DP83826E_STATUS_WRITE_ERROR           ((int32_t)-4)
#define  DP83826E_STATUS_ADDRESS_ERROR         ((int32_t)-3)
#define  DP83826E_STATUS_RESET_TIMEOUT         ((int32_t)-2)
#define  DP83826E_STATUS_ERROR                 ((int32_t)-1)
#define  DP83826E_STATUS_OK                    ((int32_t) 0)
#define  DP83826E_STATUS_LINK_DOWN             ((int32_t) 1)
#define  DP83826E_STATUS_100MBITS_FULLDUPLEX   ((int32_t) 2)
#define  DP83826E_STATUS_100MBITS_HALFDUPLEX   ((int32_t) 3)
#define  DP83826E_STATUS_10MBITS_FULLDUPLEX    ((int32_t) 4)
#define  DP83826E_STATUS_10MBITS_HALFDUPLEX    ((int32_t) 5)
#define  DP83826E_STATUS_AUTONEGO_NOTDONE      ((int32_t) 6)
/**
  * @}
  */

/** @defgroup LAN8742_IT_Flags LAN8742 IT Flags
  * @{
  */
#define  DP83826E_WOL_IT                        LAN8742_INT_8
#define  DP83826E_ENERGYON_IT                   LAN8742_INT_7
#define  DP83826E_AUTONEGO_COMPLETE_IT          LAN8742_INT_6
#define  DP83826E_REMOTE_FAULT_IT               LAN8742_INT_5
#define  DP83826E_LINK_DOWN_IT                  LAN8742_INT_4
#define  DP83826E_AUTONEGO_LP_ACK_IT            LAN8742_INT_3
#define  DP83826E_PARALLEL_DETECTION_FAULT_IT   LAN8742_INT_2
#define  DP83826E_AUTONEGO_PAGE_RECEIVED_IT     LAN8742_INT_1
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LAN8742_Exported_Types LAN8742 Exported Types
  * @{
  */
typedef int32_t  (*dp83826e_Init_Func) (void);
typedef int32_t  (*dp83826e_DeInit_Func) (void);
typedef int32_t  (*dp83826e_ReadReg_Func)   (uint32_t, uint32_t, uint32_t *);
typedef int32_t  (*dp83826e_WriteReg_Func)  (uint32_t, uint32_t, uint32_t);
typedef int32_t  (*dp83826e_GetTick_Func)  (void);

typedef struct
{
	dp83826e_Init_Func      Init;
  dp83826e_DeInit_Func    DeInit;
  dp83826e_WriteReg_Func  WriteReg;
  dp83826e_ReadReg_Func   ReadReg;
  dp83826e_GetTick_Func   GetTick;
} dp83826e_IOCtx_t;


typedef struct
{
  uint32_t            DevAddr;
  uint32_t            Is_Initialized;
  dp83826e_IOCtx_t     IO;
  void               *pData;
}dp83826e_Object_t;
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup LAN8742_Exported_Functions LAN8742 Exported Functions
  * @{
  */
int32_t DP83826E_RegisterBusIO(dp83826e_Object_t *pObj, dp83826e_IOCtx_t *ioctx);
int32_t DP83826E_Init(dp83826e_Object_t *pObj);
int32_t DP83826E_DeInit(dp83826e_Object_t *pObj);
int32_t DP83826E_DisablePowerDownMode(dp83826e_Object_t *pObj);
int32_t DP83826E_EnablePowerDownMode(dp83826e_Object_t *pObj);
int32_t DP83826E_StartAutoNego(dp83826e_Object_t *pObj);
int32_t DP83826E_GetLinkState(dp83826e_Object_t *pObj);
int32_t DP83826E_SetLinkState(dp83826e_Object_t *pObj, uint32_t LinkState);
int32_t DP83826E_EnableLoopbackMode(dp83826e_Object_t *pObj);
int32_t DP83826E_DisableLoopbackMode(dp83826e_Object_t *pObj);
int32_t DP83826E_EnableIT(dp83826e_Object_t *pObj, uint32_t Interrupt);
int32_t DP83826E_DisableIT(dp83826e_Object_t *pObj, uint32_t Interrupt);
int32_t DP83826E_ClearIT(dp83826e_Object_t *pObj, uint32_t Interrupt);
int32_t DP83826E_GetITStatus(dp83826e_Object_t *pObj, uint32_t Interrupt);


int32_t DP83826E_FindFirstPHY(dp83826e_Object_t *pObj);
int32_t DP83826E_SoftwareReset(dp83826e_Object_t *pObj);
int32_t DP83826E_Configure(dp83826e_Object_t *pObj);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_DP83826E_H_ */
