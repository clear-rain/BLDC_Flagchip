#ifndef _DEVICE_FEATURES_FLAGCHIP_FLEXCAN_COMMON_H_
#define _DEVICE_FEATURES_FLAGCHIP_FLEXCAN_COMMON_H_

#define FLEXCAN_MB_RAM_OFFSET         0x80U     /* length is MB_Num*4*4 */
#define FLEXCAN_RXIMR_OFFSET          0x880U    /* Length is MB_Num*4 */
#define FLEXCAN_RXFIR_TEST_OFFSET     0xA80U
#define FLEXCAN_RXFIR_TEST_LEN        0x18U     /* Length is 0x18     */
#define FLEXCAN_MASK_OFFSET           0xAA0U
#define FLEXCAN_MASK_LEN              0x10U     /* Length is 0x10, RX14MASK, RX15MASK,RXMGMAXK, and RSFGMASK */
#define FLEXCAN_SMBTX_OFFSET          0xAB0U
#define FLEXCAN_SMBTX_LEN             0x10U     /* Length is 0x10     */
#define FLEXCAN_SMBRX0_OFFSET         0xAC0U
#define FLEXCAN_SMBRX0_LEN            0x10U     /* Length is 0x10     */
#define FLEXCAN_SMBRX1_OFFSET         0xAD0U
#define FLEXCAN_SMBRX1_LEN            0x10U     /* Length is 0x10     */
#define FLEXCAN_FD_SMBTX_OFFSET       0xF28U
#define FLEXCAN_FD_SMBTX_LEN          0x48U     /* Length is 0x48     */
#define FLEXCAN_FD_SMBRX0_OFFSET      0xF70U
#define FLEXCAN_FD_SMBRX0_LEN         0x48U     /* Length is 0x48     */
#define FLEXCAN_FD_SMBRX1_OFFSET      0xFB8U
#define FLEXCAN_FD_SMBRX1_LEN         0x48U     /* Length is 0x48     */
#define FLEXCAN_ERX_FIFO_OFFSET       0x2000U   /* Length is Depth*20(fd) or Depth*6(non-fd) */
#define FLEXCAN_ERX_FIFO_FD_WIDTH     20U
#define FLEXCAN_ERX_FIFO_NONFD_WIDTH  6U
#define FLEXCAN_ERFFEL_OFFSET         0x3000U   /* Length is element_num*4 */
#define FLEXCAN_GATEBUF_OFFSET        0x1A10U   /* Length is gatebuf_num*2*4 */


#endif /* _DEVICE_FEATURES_FLAGCHIP_FLEXCAN_COMMON_H_ */
