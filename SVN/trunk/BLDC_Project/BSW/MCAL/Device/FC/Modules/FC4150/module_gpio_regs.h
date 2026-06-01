#ifndef _MODULE_GPIO_KJO_Ufdi33_REGS_H_
#define _MODULE_GPIO_KJO_Ufdi33_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
#include "typedef.h"
/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */
/** GPIO - Size of Registers Arrays */
/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t PDOR                          ; /* Port Data Output Register, offset: 0x0 */
  __O  uint32_t PSOR                          ; /* Port Set Output Register, offset: 0x4 */
  __O  uint32_t PCOR                          ; /* Port Clear Output Register, offset: 0x8 */
  __O  uint32_t PTOR                          ; /* Port Toggle Output Register, offset: 0xC */
  __I  uint32_t PDIR                          ; /* Port Data Input Register, offset: 0x10 */
  __IO uint32_t PDDR                          ; /* Port Data Direction Register, offset: 0x14 */
  __IO uint32_t PIDR                          ; /* Port Input Disable Register, offset: 0x18 */
} GPIO_Type, *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */
 
/* PDOR Bit Fields */
#define GPIO_PDOR_PDO_MASK             0xFFFFFFFFu
#define GPIO_PDOR_PDO_SHIFT            0u
#define GPIO_PDOR_PDO_WIDTH            32u
#define GPIO_PDOR_PDO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)
/* PDOR Reg Mask */
#define GPIO_PDOR_MASK                 0xFFFFFFFFu
/* PSOR Bit Fields */
#define GPIO_PSOR_PSO_MASK             0xFFFFFFFFu
#define GPIO_PSOR_PSO_SHIFT            0u
#define GPIO_PSOR_PSO_WIDTH            32u
#define GPIO_PSOR_PSO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PSOR_PSO_SHIFT))&GPIO_PSOR_PSO_MASK)
/* PSOR Reg Mask */
#define GPIO_PSOR_MASK                 0xFFFFFFFFu
/* PCOR Bit Fields */
#define GPIO_PCOR_PCO_MASK             0xFFFFFFFFu
#define GPIO_PCOR_PCO_SHIFT            0u
#define GPIO_PCOR_PCO_WIDTH            32u
#define GPIO_PCOR_PCO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PCOR_PCO_SHIFT))&GPIO_PCOR_PCO_MASK)
/* PCOR Reg Mask */
#define GPIO_PCOR_MASK                 0xFFFFFFFFu
/* PTOR Bit Fields */
#define GPIO_PTOR_PTO_MASK             0xFFFFFFFFu
#define GPIO_PTOR_PTO_SHIFT            0u
#define GPIO_PTOR_PTO_WIDTH            32u
#define GPIO_PTOR_PTO(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PTOR_PTO_SHIFT))&GPIO_PTOR_PTO_MASK)
/* PTOR Reg Mask */
#define GPIO_PTOR_MASK                 0xFFFFFFFFu
/* PDIR Bit Fields */
#define GPIO_PDIR_PDI_MASK             0xFFFFFFFFu
#define GPIO_PDIR_PDI_SHIFT            0u
#define GPIO_PDIR_PDI_WIDTH            32u
#define GPIO_PDIR_PDI(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PDIR_PDI_SHIFT))&GPIO_PDIR_PDI_MASK)
/* PDIR Reg Mask */
#define GPIO_PDIR_MASK                 0xFFFFFFFFu
/* PDDR Bit Fields */
#define GPIO_PDDR_PDD_MASK             0xFFFFFFFFu
#define GPIO_PDDR_PDD_SHIFT            0u
#define GPIO_PDDR_PDD_WIDTH            32u
#define GPIO_PDDR_PDD(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)
/* PDDR Reg Mask */
#define GPIO_PDDR_MASK                 0xFFFFFFFFu
/* PIDR Bit Fields */
#define GPIO_PIDR_PID_MASK             0xFFFFFFFFu
#define GPIO_PIDR_PID_SHIFT            0u
#define GPIO_PIDR_PID_WIDTH            32u
#define GPIO_PIDR_PID(x)               (((uint32_t)(((uint32_t)(x))<<GPIO_PIDR_PID_SHIFT))&GPIO_PIDR_PID_MASK)
/* PIDR Reg Mask */
#define GPIO_PIDR_MASK                 0xFFFFFFFFu
/**
 * @}
 */ /* end of group GPIO_Register_Masks */
/**
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
