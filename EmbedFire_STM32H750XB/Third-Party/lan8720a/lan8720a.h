/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LAN8720A_H__
#define LAN8720A_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported define -----------------------------------------------------------*/
/** @defgroup LAN8720A_Registers_Mapping LAN8720A Registers Mapping
  * @{
  */ 
#define LAN8720A_ADDR		0
#define LAN8720A_TIMEOUT	500
/**
  * @}
  */
	 
/** @defgroup LAN8720A_Registers_Mapping LAN8720A Registers Mapping
  * @{
  */ 
#define LAN8720A_BCR      ((uint16_t)0x0000U)		// Basic Control Register
#define LAN8720A_BSR      ((uint16_t)0x0001U)		// Basic Status Register
#define LAN8720A_PHYI1R   ((uint16_t)0x0002U)		// PHY Identifier 1
#define LAN8720A_PHYI2R   ((uint16_t)0x0003U)		// PHY Identifier 2
#define LAN8720A_ANAR     ((uint16_t)0x0004U)		// Auto-Negotiation Advertisement Register
#define LAN8720A_ANLPAR   ((uint16_t)0x0005U)		// Auto-Negotiation Link Partner Ability Register
#define LAN8720A_ANER     ((uint16_t)0x0006U)		// Auto-Negotiation Expansion Register
#define LAN8720A_MCSR     ((uint16_t)0x0011U)		// Mode Control/Status Register
#define LAN8720A_SMR      ((uint16_t)0x0012U)		// Special Modes
#define LAN8720A_SECR     ((uint16_t)0x001AU)		// Symbol Error Counter Register
#define LAN8720A_SCSIR    ((uint16_t)0x001BU)		// Control / Status Indication Register
#define LAN8720A_ISR      ((uint16_t)0x001DU)		// Interrupt Source Register
#define LAN8720A_IMR      ((uint16_t)0x001EU)		// Interrupt Mask Register
#define LAN8720A_PHYSCSR  ((uint16_t)0x001FU)		// PHY Special Control/Status Register
/**
  * @}
  */

/** @defgroup LAN8720A_BCR_Bit_Definition LAN8720A BCR Bit Definition
  * @{
  */    
#define LAN8720A_BCR_SOFT_RESET         ((uint16_t)0x8000U)
#define LAN8720A_BCR_LOOPBACK           ((uint16_t)0x4000U)
#define LAN8720A_BCR_SPEED_SELECT       ((uint16_t)0x2000U)
#define LAN8720A_BCR_AUTONEGO_EN        ((uint16_t)0x1000U)
#define LAN8720A_BCR_POWER_DOWN         ((uint16_t)0x0800U)
#define LAN8720A_BCR_ISOLATE            ((uint16_t)0x0400U)
#define LAN8720A_BCR_RESTART_AUTONEGO   ((uint16_t)0x0200U)
#define LAN8720A_BCR_DUPLEX_MODE        ((uint16_t)0x0100U) 
/**
  * @}
  */

/** @defgroup LAN8720A_BSR_Bit_Definition LAN8720A BSR Bit Definition
  * @{
  */   
#define LAN8720A_BSR_100BASE_T4       ((uint16_t)0x8000U)
#define LAN8720A_BSR_100BASE_TX_FD    ((uint16_t)0x4000U)
#define LAN8720A_BSR_100BASE_TX_HD    ((uint16_t)0x2000U)
#define LAN8720A_BSR_10BASE_T_FD      ((uint16_t)0x1000U)
#define LAN8720A_BSR_10BASE_T_HD      ((uint16_t)0x0800U)
#define LAN8720A_BSR_100BASE_T2_FD    ((uint16_t)0x0400U)
#define LAN8720A_BSR_100BASE_T2_HD    ((uint16_t)0x0200U)
#define LAN8720A_BSR_EXTENDED_STATUS  ((uint16_t)0x0100U)
#define LAN8720A_BSR_AUTONEGO_CPLT    ((uint16_t)0x0020U)
#define LAN8720A_BSR_REMOTE_FAULT     ((uint16_t)0x0010U)
#define LAN8720A_BSR_AUTONEGO_ABILITY ((uint16_t)0x0008U)
#define LAN8720A_BSR_LINK_STATUS      ((uint16_t)0x0004U)
#define LAN8720A_BSR_JABBER_DETECT    ((uint16_t)0x0002U)
#define LAN8720A_BSR_EXTENDED_CAP     ((uint16_t)0x0001U)
/**
  * @}
  */

/** @defgroup LAN8720A_PHYI1R_Bit_Definition LAN8720A PHYI1R Bit Definition
  * @{
  */
#define LAN8720A_PHYI1R_OUI_3_18           ((uint16_t)0xFFFFU)
/**
  * @}
  */

/** @defgroup LAN8720A_PHYI2R_Bit_Definition LAN8720A PHYI2R Bit Definition
  * @{
  */
#define LAN8720A_PHYI2R_OUI_19_24          ((uint16_t)0xFC00U)
#define LAN8720A_PHYI2R_MODEL_NBR          ((uint16_t)0x03F0U)
#define LAN8720A_PHYI2R_REVISION_NBR       ((uint16_t)0x000FU)
/**
  * @}
  */

/** @defgroup LAN8720A_ANAR_Bit_Definition LAN8720A ANAR Bit Definition
  * @{
  */
#define LAN8720A_ANAR_NEXT_PAGE               ((uint16_t)0x8000U)
#define LAN8720A_ANAR_REMOTE_FAULT            ((uint16_t)0x2000U)
#define LAN8720A_ANAR_PAUSE_OPERATION         ((uint16_t)0x0C00U)
#define LAN8720A_ANAR_PO_NOPAUSE              ((uint16_t)0x0000U)
#define LAN8720A_ANAR_PO_SYMMETRIC_PAUSE      ((uint16_t)0x0400U)
#define LAN8720A_ANAR_PO_ASYMMETRIC_PAUSE     ((uint16_t)0x0800U)
#define LAN8720A_ANAR_PO_ADVERTISE_SUPPORT    ((uint16_t)0x0C00U)
#define LAN8720A_ANAR_100BASE_TX_FD           ((uint16_t)0x0100U)
#define LAN8720A_ANAR_100BASE_TX              ((uint16_t)0x0080U)
#define LAN8720A_ANAR_10BASE_T_FD             ((uint16_t)0x0040U)
#define LAN8720A_ANAR_10BASE_T                ((uint16_t)0x0020U)
#define LAN8720A_ANAR_SELECTOR_FIELD          ((uint16_t)0x000FU)
/**
  * @}
  */

/** @defgroup LAN8720A_ANLPAR_Bit_Definition LAN8720A ANLPAR Bit Definition
  * @{
  */
#define LAN8720A_ANLPAR_NEXT_PAGE            ((uint16_t)0x8000U)
#define LAN8720A_ANLPAR_ACKNOWLEDGE          ((uint16_t)0x4000U)
#define LAN8720A_ANLPAR_REMOTE_FAULT         ((uint16_t)0x2000U)
#define LAN8720A_ANLPAR_PAUSE_OPERATION      ((uint16_t)0x0400U)
#define LAN8720A_ANLPAR_100BASE_T4        	 ((uint16_t)0x0200U)
#define LAN8720A_ANLPAR_100BASE_TX_FD		 ((uint16_t)0x0100U)
#define LAN8720A_ANLPAR_100BASE_TX           ((uint16_t)0x0080U)
#define LAN8720A_ANLPAR_10BASE_T_FD          ((uint16_t)0x0040U)
#define LAN8720A_ANLPAR_10BASE_T             ((uint16_t)0x0020U)
#define LAN8720A_ANLPAR_SELECTOR_FIELD       ((uint16_t)0x001FU)
/**
  * @}
  */

/** @defgroup LAN8720A_ANER_Bit_Definition LAN8720A ANER Bit Definition
  * @{
  */
#define LAN8720A_ANER_PARALLEL_DETECT_FAULT  ((uint16_t)0x0010U)
#define LAN8720A_ANER_LP_NP_ABLE             ((uint16_t)0x0008U)
#define LAN8720A_ANER_NP_ABLE                ((uint16_t)0x0004U)
#define LAN8720A_ANER_PAGE_RECEIVED          ((uint16_t)0x0002U)
#define LAN8720A_ANER_LP_AUTONEG_ABLE        ((uint16_t)0x0001U)
/**
  * @}
  */

/** @defgroup LAN8720A_MCSR_Bit_Definition LAN8720A MCSR Bit Definition
  * @{
  */
#define LAN8720A_MCSR_EDPWRDOWN        ((uint16_t)0x2000U)
#define LAN8720A_MCSR_FARLOOPBACK      ((uint16_t)0x0200U)
#define LAN8720A_MCSR_ALTINT           ((uint16_t)0x0040U)
#define LAN8720A_MCSR_ENERGYON         ((uint16_t)0x0002U)
/**
  * @}
  */

/** @defgroup LAN8720A_SMR_Bit_Definition LAN8720A SMR Bit Definition
  * @{
  */
#define LAN8720A_SMR_MODE       ((uint16_t)0x00E0U)
#define LAN8720A_SMR_PHY_ADDR   ((uint16_t)0x001FU)
/**
  * @}
  */
  
/** @defgroup LAN8720A_SECR_Bit_Definition LAN8720A SECR Bit Definition
  * @{
  */
#define LAN8720A_SECR_SYM_ERR_CNT   	((uint16_t)0xFFFFU)
/**
  * @}
  */

/** @defgroup LAN8720A_SCSIR_Bit_Definition LAN8720A SCSIR Bit Definition
  * @{
  */
#define LAN8720A_SCSIR_AUTO_MDIX_ENABLE    ((uint16_t)0x8000U)
#define LAN8720A_SCSIR_CHANNEL_SELECT      ((uint16_t)0x2000U)
#define LAN8720A_SCSIR_SQE_DISABLE         ((uint16_t)0x0800U)
#define LAN8720A_SCSIR_XPOLALITY           ((uint16_t)0x0010U)
/**
  * @}
  */

/** @defgroup LAN8720A_IMR_ISFR_Bit_Definition LAN8720A IMR ISFR Bit Definition
  * @{
  */
#define LAN8720A_ISFR_INT8       ((uint16_t)0x0100U)
#define LAN8720A_ISFR_INT7       ((uint16_t)0x0080U)
#define LAN8720A_ISFR_INT6       ((uint16_t)0x0040U)
#define LAN8720A_ISFR_INT5       ((uint16_t)0x0020U)
#define LAN8720A_ISFR_INT4       ((uint16_t)0x0010U)
#define LAN8720A_ISFR_INT3       ((uint16_t)0x0008U)
#define LAN8720A_ISFR_INT2       ((uint16_t)0x0004U)
#define LAN8720A_ISFR_INT1       ((uint16_t)0x0002U)
/**
  * @}
  */
  
/** @defgroup LAN8720A_IMR_Bit_Definition LAN8720A IMR Bit Definition
  * @{
  */
#define LAN8720A_IMR_MASK_BITS   	((uint16_t)0x00FEU)
/**
  * @}
  */


/** @defgroup LAN8720A_PHYSCSR_Bit_Definition LAN8720A PHYSCSR Bit Definition
  * @{
  */
#define LAN8720A_PHYSCSR_AUTONEGO_DONE   ((uint16_t)0x1000U)
#define LAN8720A_PHYSCSR_HCDSPEEDMASK    ((uint16_t)0x001CU)
#define LAN8720A_PHYSCSR_10BT_HD         ((uint16_t)0x0004U)
#define LAN8720A_PHYSCSR_10BT_FD         ((uint16_t)0x0014U)
#define LAN8720A_PHYSCSR_100BTX_HD       ((uint16_t)0x0008U)
#define LAN8720A_PHYSCSR_100BTX_FD       ((uint16_t)0x0018U)
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/ 
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
int lan8720a_init(void);
int lan8720a_read_phy(uint16_t reg, uint32_t *regval);
int lan8720a_write_phy(uint16_t reg, uint16_t value);
void lan8720a_enable_powerdown_mode(void);
void lan8720a_disable_powerdown_mode(void);
void lan8720a_startautonego(void);  
uint32_t lan8720a_getlinkstate(void);
void lan8720a_setlinkstate(uint32_t linkstate);

#ifdef __cplusplus
}
#endif
#endif /* LAN8720A_H */


/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */       
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

