#ifndef _IMXRT1062_H
#define _IMXRT1062_H

#include <stdint.h>
#include <arch/arm_v7m.h>

#define DMAMEM __attribute__ ((section(".dmabuffers"), used))
#define FASTRUN __attribute__ ((section(".fastrun") ))
#define PROGMEM __attribute__((section(".progmem")))
#define FLASHMEM __attribute__((section(".flashmem")))
#define EXTMEM __attribute__((section(".externalram")))

#define IMXRT1062_IVT_HEADER(TAG, LEN, VERSION) ((TAG & 0xff) | (LEN << 8) & 0xffff | ((VERSION << 24) & 0xff)) 0x432000d1

#define IMXRT1062_IRQ_DMA_CH0           0
#define IMXRT1062_IRQ_DMA_CH1           1
#define IMXRT1062_IRQ_DMA_CH2           2
#define IMXRT1062_IRQ_DMA_CH3           3
#define IMXRT1062_IRQ_DMA_CH4           4
#define IMXRT1062_IRQ_DMA_CH5           5
#define IMXRT1062_IRQ_DMA_CH6           6
#define IMXRT1062_IRQ_DMA_CH7           7
#define IMXRT1062_IRQ_DMA_CH8           8
#define IMXRT1062_IRQ_DMA_CH9           9
#define IMXRT1062_IRQ_DMA_CH10          10
#define IMXRT1062_IRQ_DMA_CH11          11
#define IMXRT1062_IRQ_DMA_CH12          12
#define IMXRT1062_IRQ_DMA_CH13          13
#define IMXRT1062_IRQ_DMA_CH14          14
#define IMXRT1062_IRQ_DMA_CH15          15
#define IMXRT1062_IRQ_DMA_ERROR         16
#define IMXRT1062_IRQ_CTI0              17
#define IMXRT1062_IRQ_CTI1              18
#define IMXRT1062_IRQ_CORE_ERROR        19 // TODO - name?
#define IMXRT1062_IRQ_LPUART1           20
#define IMXRT1062_IRQ_LPUART2           21
#define IMXRT1062_IRQ_LPUART3           22
#define IMXRT1062_IRQ_LPUART4           23
#define IMXRT1062_IRQ_LPUART5           24
#define IMXRT1062_IRQ_LPUART6           25
#define IMXRT1062_IRQ_LPUART7           26
#define IMXRT1062_IRQ_LPUART8           27
#define IMXRT1062_IRQ_LPI2C1            28
#define IMXRT1062_IRQ_LPI2C2            29
#define IMXRT1062_IRQ_LPI2C3            30
#define IMXRT1062_IRQ_LPI2C4            31
#define IMXRT1062_IRQ_LPSPI1            32
#define IMXRT1062_IRQ_LPSPI2            33
#define IMXRT1062_IRQ_LPSPI3            34
#define IMXRT1062_IRQ_LPSPI4            35
#define IMXRT1062_IRQ_CAN1              36
#define IMXRT1062_IRQ_CAN2              37
#define IMXRT1062_IRQ_ADDR_ERR          38 // TODO: name?
#define IMXRT1062_IRQ_KPP               39
#define IMXRT1062_IRQ_TSC_DIG           40
#define IMXRT1062_IRQ_GPR_IRQ           41
#define IMXRT1062_IRQ_LCDIF             42
#define IMXRT1062_IRQ_CSI               43
#define IMXRT1062_IRQ_PXP               44
#define IMXRT1062_IRQ_WDOG2             45
#define IMXRT1062_IRQ_SNVS_IRQ          46
#define IMXRT1062_IRQ_SNVS_SECURITY     47
#define IMXRT1062_IRQ_SNVS_ONOFF        48
#define IMXRT1062_IRQ_CSU               49
#define IMXRT1062_IRQ_DCP0              50 // TODO: ???
#define IMXRT1062_IRQ_DCP1              51 // TODO: ???
#define IMXRT1062_IRQ_DCP2              52 // TODO: ???
#define IMXRT1062_IRQ_TRNG              53
#define IMXRT1062_IRQ_SJC_IRQ           54
#define IMXRT1062_IRQ_BEE               55
#define IMXRT1062_IRQ_SAI1              56
#define IMXRT1062_IRQ_SAI2              57
#define IMXRT1062_IRQ_SAI3_RX           58
#define IMXRT1062_IRQ_SAI3_TX           59
#define IMXRT1062_IRQ_SPDIF             60
#define IMXRT1062_IRQ_BROWNOUT0         61
#define IMXRT1062_IRQ_Reserved1         62
#define IMXRT1062_IRQ_TEMPERATURE       63
#define IMXRT1062_IRQ_TEMPERATURE_PANIC 64
#define IMXRT1062_IRQ_USBPHY0           65
#define IMXRT1062_IRQ_USBPHY1           66
#define IMXRT1062_IRQ_ADC1              67
#define IMXRT1062_IRQ_ADC2              68
#define IMXRT1062_IRQ_DCDC              69
#define IMXRT1062_IRQ_SOFTWARE          70
#define IMXRT1062_IRQ_Reserved2         71
#define IMXRT1062_IRQ_GPIO1_INT0        72
#define IMXRT1062_IRQ_GPIO1_INT1        73
#define IMXRT1062_IRQ_GPIO1_INT2        74
#define IMXRT1062_IRQ_GPIO1_INT3        75
#define IMXRT1062_IRQ_GPIO1_INT4        76
#define IMXRT1062_IRQ_GPIO1_INT5        77
#define IMXRT1062_IRQ_GPIO1_INT6        78
#define IMXRT1062_IRQ_GPIO1_INT7        79
#define IMXRT1062_IRQ_GPIO1_0_15        80
#define IMXRT1062_IRQ_GPIO1_16_31       81
#define IMXRT1062_IRQ_GPIO2_0_15        82
#define IMXRT1062_IRQ_GPIO2_16_31       83
#define IMXRT1062_IRQ_GPIO3_0_15        84
#define IMXRT1062_IRQ_GPIO3_16_31       85
#define IMXRT1062_IRQ_GPIO4_0_15        86
#define IMXRT1062_IRQ_GPIO4_16_31       87
#define IMXRT1062_IRQ_GPIO5_0_15        88
#define IMXRT1062_IRQ_GPIO5_16_31       89
#define IMXRT1062_IRQ_FLEXIO1           90
#define IMXRT1062_IRQ_FLEXIO2           91
#define IMXRT1062_IRQ_WDOG1             92
#define IMXRT1062_IRQ_RTWDOG            93
#define IMXRT1062_IRQ_EWM               94
#define IMXRT1062_IRQ_CCM1              95
#define IMXRT1062_IRQ_CCM2              96
#define IMXRT1062_IRQ_GPC               97
#define IMXRT1062_IRQ_SRC               98
#define IMXRT1062_IRQ_Reserved3         99
#define IMXRT1062_IRQ_GPT1              100
#define IMXRT1062_IRQ_GPT2              101
#define IMXRT1062_IRQ_FLEXPWM1_0        102
#define IMXRT1062_IRQ_FLEXPWM1_1        103
#define IMXRT1062_IRQ_FLEXPWM1_2        104
#define IMXRT1062_IRQ_FLEXPWM1_3        105
#define IMXRT1062_IRQ_FLEXPWM1_FAULT    106
#define IMXRT1062_IRQ_FLEXSPI2          107 // RT1060 only
#define IMXRT1062_IRQ_FLEXSPI           108
#define IMXRT1062_IRQ_SEMC              109
#define IMXRT1062_IRQ_SDHC1             110
#define IMXRT1062_IRQ_SDHC2             111
#define IMXRT1062_IRQ_USB2              112
#define IMXRT1062_IRQ_USB1              113
#define IMXRT1062_IRQ_ENET              114
#define IMXRT1062_IRQ_ENET_TIMER        115
#define IMXRT1062_IRQ_XBAR1_01          116
#define IMXRT1062_IRQ_XBAR1_23          117
#define IMXRT1062_IRQ_ADC_ETC0          118
#define IMXRT1062_IRQ_ADC_ETC1          119
#define IMXRT1062_IRQ_ADC_ETC2          120
#define IMXRT1062_IRQ_ADC_ETC_ERR       121
#define IMXRT1062_IRQ_PIT               122
#define IMXRT1062_IRQ_ACMP1             123
#define IMXRT1062_IRQ_ACMP2             124
#define IMXRT1062_IRQ_ACMP3             125
#define IMXRT1062_IRQ_ACMP4             126
#define IMXRT1062_IRQ_Reserved4         127
#define IMXRT1062_IRQ_Reserved5         128
#define IMXRT1062_IRQ_ENC1              129
#define IMXRT1062_IRQ_ENC2              130
#define IMXRT1062_IRQ_ENC3              131
#define IMXRT1062_IRQ_ENC4              132
#define IMXRT1062_IRQ_QTIMER1           133
#define IMXRT1062_IRQ_QTIMER2           134
#define IMXRT1062_IRQ_QTIMER3           135
#define IMXRT1062_IRQ_QTIMER4           136
#define IMXRT1062_IRQ_FLEXPWM2_0        137
#define IMXRT1062_IRQ_FLEXPWM2_1        138
#define IMXRT1062_IRQ_FLEXPWM2_2        139
#define IMXRT1062_IRQ_FLEXPWM2_3        140
#define IMXRT1062_IRQ_FLEXPWM2_FAULT    141
#define IMXRT1062_IRQ_FLEXPWM3_0        142
#define IMXRT1062_IRQ_FLEXPWM3_1        143
#define IMXRT1062_IRQ_FLEXPWM3_2        144
#define IMXRT1062_IRQ_FLEXPWM3_3        145
#define IMXRT1062_IRQ_FLEXPWM3_FAULT    146
#define IMXRT1062_IRQ_FLEXPWM4_0        147
#define IMXRT1062_IRQ_FLEXPWM4_1        148
#define IMXRT1062_IRQ_FLEXPWM4_2        149
#define IMXRT1062_IRQ_FLEXPWM4_3        150
#define IMXRT1062_IRQ_FLEXPWM4_FAULT    151
#define IMXRT1062_IRQ_ENET2             152 // RT1060 only
#define IMXRT1062_IRQ_ENET2_TIMER       153 // RT1060 only
#define IMXRT1062_IRQ_CAN3              154 // RT1060 only
#define IMXRT1062_IRQ_Reserved6         155
#define IMXRT1062_IRQ_FLEXIO3           156 // RT1060 only
#define IMXRT1062_IRQ_GPIO6789          157 // RT1060 only
#define IMXRT1062_IRQ_SJC_DEBUG         158
#define IMXRT1062_IRQ_NMI_WAKEUP        159

#define IMXRT1062_NVIC_NUM_INTERRUPTS    160

// IOMUXC GPR registers require CCM_CCGR4_IOMUXC_GPR
/* i.MX RT1060X Processor Reference Manual, Rev. 1, 11.3, p323 */
#define IMXRT1062_IOMUXC_GPR_BASE	0x400ac000
#define IMXRT1062_IOMUXC_GPR_GPR0	0x00
#define IMXRT1062_IOMUXC_GPR_GPR1	0x04
#define IMXRT1062_IOMUXC_GPR_GPR2	0x08
#define IMXRT1062_IOMUXC_GPR_GPR3	0x0c
#define IMXRT1062_IOMUXC_GPR_GPR4	0x10
#define IMXRT1062_IOMUXC_GPR_GPR5	0x14
#define IMXRT1062_IOMUXC_GPR_GPR6	0x18
#define IMXRT1062_IOMUXC_GPR_GPR7	0x1c
#define IMXRT1062_IOMUXC_GPR_GPR8   0x20
#define IMXRT1062_IOMUXC_GPR_GPR9	0x24
#define IMXRT1062_IOMUXC_GPR_GPR10	0x28
#define IMXRT1062_IOMUXC_GPR_GPR11	0x2c
#define IMXRT1062_IOMUXC_GPR_GPR12	0x30
#define IMXRT1062_IOMUXC_GPR_GPR13	0x34
#define IMXRT1062_IOMUXC_GPR_GPR14	0x38
#define IMXRT1062_IOMUXC_GPR_GPR15	0x3c
#define IMXRT1062_IOMUXC_GPR_GPR16	0x40
#define IMXRT1062_IOMUXC_GPR_GPR17	0x44
#define IMXRT1062_IOMUXC_GPR_GPR18	0x48
#define IMXRT1062_IOMUXC_GPR_GPR19	0x4c
#define IMXRT1062_IOMUXC_GPR_GPR20	0x50
#define IMXRT1062_IOMUXC_GPR_GPR21	0x54
#define IMXRT1062_IOMUXC_GPR_GPR22	0x58
#define IMXRT1062_IOMUXC_GPR_GPR23	0x5c
#define IMXRT1062_IOMUXC_GPR_GPR24	0x60
#define IMXRT1062_IOMUXC_GPR_GPR25	0x64
#define IMXRT1062_IOMUXC_GPR_GPR26	0x68
#define IMXRT1062_IOMUXC_GPR_GPR27	0x6c
#define IMXRT1062_IOMUXC_GPR_GPR28	0x70
#define IMXRT1062_IOMUXC_GPR_GPR29	0x74
#define IMXRT1062_IOMUXC_GPR_GPR30	0x78
#define IMXRT1062_IOMUXC_GPR_GPR31	0x7c
#define IMXRT1062_IOMUXC_GPR_GPR32	0x80
#define IMXRT1062_IOMUXC_GPR_GPR33	0x84
#define IMXRT1062_IOMUXC_GPR_GPR34	0x88

#define IMXRT1062_IOMUXC_GPR_WRITE(OFFS, VALUE)  (*(volatile uint32_t *)((IMXRT1062_IOMUXC_GPR_BASE) + (OFFS))) = (VALUE)
#define IMXRT1062_IOMUXC_GPR_READ(OFFS)          (*(volatile uint32_t *)((IMXRT1062_IOMUXC_GPR_BASE) + (OFFS)))

#endif
