#ifndef _IMXRT1062_H
#define _IMXRT1062_H

#include <stdint.h>

#define DMAMEM __attribute__ ((section(".dmabuffers"), used))
#define FASTRUN __attribute__ ((section(".fastrun") ))
#define PROGMEM __attribute__((section(".progmem")))
#define FLASHMEM __attribute__((section(".flashmem")))
#define EXTMEM __attribute__((section(".externalram")))

enum IRQ_NUMBER_t {
        IRQ_DMA_CH0 =           0,
        IRQ_DMA_CH1 =           1,
        IRQ_DMA_CH2 =           2,
        IRQ_DMA_CH3 =           3,
        IRQ_DMA_CH4 =           4,
        IRQ_DMA_CH5 =           5,
        IRQ_DMA_CH6 =           6,
        IRQ_DMA_CH7 =           7,
        IRQ_DMA_CH8 =           8,
        IRQ_DMA_CH9 =           9,
        IRQ_DMA_CH10 =          10,
        IRQ_DMA_CH11 =          11,
        IRQ_DMA_CH12 =          12,
        IRQ_DMA_CH13 =          13,
        IRQ_DMA_CH14 =          14,
        IRQ_DMA_CH15 =          15,
        IRQ_DMA_ERROR =         16,
        IRQ_CTI0 =              17,
        IRQ_CTI1 =              18,
        IRQ_CORE_ERROR =        19, // TODO - name?
        IRQ_LPUART1 =           20,
        IRQ_LPUART2 =           21,
        IRQ_LPUART3 =           22,
        IRQ_LPUART4 =           23,
        IRQ_LPUART5 =           24,
        IRQ_LPUART6 =           25,
        IRQ_LPUART7 =           26,
        IRQ_LPUART8 =           27,
        IRQ_LPI2C1 =            28,
        IRQ_LPI2C2 =            29,
        IRQ_LPI2C3 =            30,
        IRQ_LPI2C4 =            31,
        IRQ_LPSPI1 =            32,
        IRQ_LPSPI2 =            33,
        IRQ_LPSPI3 =            34,
        IRQ_LPSPI4 =            35,
        IRQ_CAN1 =              36,
        IRQ_CAN2 =              37,
        IRQ_ADDR_ERR =          38, // TODO: name?
        IRQ_KPP =               39,
        IRQ_TSC_DIG =           40,
        IRQ_GPR_IRQ =           41,
        IRQ_LCDIF =             42,
        IRQ_CSI =               43,
        IRQ_PXP =               44,
        IRQ_WDOG2 =             45,
        IRQ_SNVS_IRQ =          46,
        IRQ_SNVS_SECURITY =     47,
        IRQ_SNVS_ONOFF =        48,
        IRQ_CSU =               49,
        IRQ_DCP0 =              50, // TODO: ???
        IRQ_DCP1 =              51, // TODO: ???
        IRQ_DCP2 =              52, // TODO: ???
        IRQ_TRNG =              53,
        IRQ_SJC_IRQ =           54,
        IRQ_BEE =               55,
        IRQ_SAI1 =              56,
        IRQ_SAI2 =              57,
        IRQ_SAI3_RX =           58,
        IRQ_SAI3_TX =           59,
        IRQ_SPDIF =             60,
        IRQ_BROWNOUT0 =         61,
        IRQ_Reserved1 =         62,
        IRQ_TEMPERATURE =       63,
        IRQ_TEMPERATURE_PANIC = 64,
        IRQ_USBPHY0 =           65,
        IRQ_USBPHY1 =           66,
        IRQ_ADC1 =              67,
        IRQ_ADC2 =              68,
        IRQ_DCDC =              69,
        IRQ_SOFTWARE =          70,
        IRQ_Reserved2 =         71,
        IRQ_GPIO1_INT0 =        72,
        IRQ_GPIO1_INT1 =        73,
        IRQ_GPIO1_INT2 =        74,
        IRQ_GPIO1_INT3 =        75,
        IRQ_GPIO1_INT4 =        76,
        IRQ_GPIO1_INT5 =        77,
        IRQ_GPIO1_INT6 =        78,
        IRQ_GPIO1_INT7 =        79,
        IRQ_GPIO1_0_15 =        80,
        IRQ_GPIO1_16_31 =       81,
        IRQ_GPIO2_0_15 =        82,
        IRQ_GPIO2_16_31 =       83,
        IRQ_GPIO3_0_15 =        84,
        IRQ_GPIO3_16_31 =       85,
        IRQ_GPIO4_0_15 =        86,
        IRQ_GPIO4_16_31 =       87,
        IRQ_GPIO5_0_15 =        88,
        IRQ_GPIO5_16_31 =       89,
        IRQ_FLEXIO1 =           90,
        IRQ_FLEXIO2 =           91,
        IRQ_WDOG1 =             92,
        IRQ_RTWDOG =            93,
        IRQ_EWM =               94,
        IRQ_CCM1 =              95,
        IRQ_CCM2 =              96,
        IRQ_GPC =               97,
        IRQ_SRC =               98,
        IRQ_Reserved3 =         99,
        IRQ_GPT1 =              100,
        IRQ_GPT2 =              101,
        IRQ_FLEXPWM1_0 =        102,
        IRQ_FLEXPWM1_1 =        103,
        IRQ_FLEXPWM1_2 =        104,
        IRQ_FLEXPWM1_3 =        105,
        IRQ_FLEXPWM1_FAULT =    106,
        IRQ_FLEXSPI2 =          107, // RT1060 only
        IRQ_FLEXSPI =           108,
        IRQ_SEMC =              109,
        IRQ_SDHC1 =             110,
        IRQ_SDHC2 =             111,
        IRQ_USB2 =              112,
        IRQ_USB1 =              113,
        IRQ_ENET =              114,
        IRQ_ENET_TIMER =        115,
        IRQ_XBAR1_01 =          116,
        IRQ_XBAR1_23 =          117,
        IRQ_ADC_ETC0 =          118,
        IRQ_ADC_ETC1 =          119,
        IRQ_ADC_ETC2 =          120,
        IRQ_ADC_ETC_ERR =       121,
        IRQ_PIT =               122,
        IRQ_ACMP1 =             123,
        IRQ_ACMP2 =             124,
        IRQ_ACMP3 =             125,
        IRQ_ACMP4 =             126,
        IRQ_Reserved4 =         127,
        IRQ_Reserved5 =         128,
        IRQ_ENC1 =              129,
        IRQ_ENC2 =              130,
        IRQ_ENC3 =              131,
        IRQ_ENC4 =              132,
        IRQ_QTIMER1 =           133,
        IRQ_QTIMER2 =           134,
        IRQ_QTIMER3 =           135,
        IRQ_QTIMER4 =           136,
        IRQ_FLEXPWM2_0 =        137,
        IRQ_FLEXPWM2_1 =        138,
        IRQ_FLEXPWM2_2 =        139,
        IRQ_FLEXPWM2_3 =        140,
        IRQ_FLEXPWM2_FAULT =    141,
        IRQ_FLEXPWM3_0 =        142,
        IRQ_FLEXPWM3_1 =        143,
        IRQ_FLEXPWM3_2 =        144,
        IRQ_FLEXPWM3_3 =        145,
        IRQ_FLEXPWM3_FAULT =    146,
        IRQ_FLEXPWM4_0 =        147,
        IRQ_FLEXPWM4_1 =        148,
        IRQ_FLEXPWM4_2 =        149,
        IRQ_FLEXPWM4_3 =        150,
        IRQ_FLEXPWM4_FAULT =    151,
        IRQ_ENET2 =             152, // RT1060 only
        IRQ_ENET2_TIMER =       153, // RT1060 only
        IRQ_CAN3 =              154, // RT1060 only
        IRQ_Reserved6 =         155,
        IRQ_FLEXIO3 =           156, // RT1060 only
        IRQ_GPIO6789 =          157, // RT1060 only
        IRQ_SJC_DEBUG =         158,
        IRQ_NMI_WAKEUP =        159
};
#define NVIC_NUM_INTERRUPTS     160

/* Arm V7M Architecture Reference Manual DDI0403E B3.2.2 */
#define SCS_BASE                (0xE000ED00)
/* CPUID Base Register */
#define SCS_CPUID               (0x0)
/* Interrupt Control and State Register */
#define SCS_ICSR                (0x4)
/* Vector Table Offset Register */
#define SCS_VTOR		        (0x8)
/* Application Interrupt and Reset Control Register */
#define SCS_AIRCR               (0xc)
/* System Control Register */
#define SCS_SCR                 (0x10)
/* Configuration and Control Register */
#define SCS_CCR                 (0x14)
/* System Handler and Priority Register 1 */
#define SCS_SHPR1               (0x18)
/* System Handler and Priority Register 2 */
#define SCS_SHPR2               (0x1c)
/* System Handler and Priority Register 3 */
#define SCS_SHPR3               (0x20)
/* System Handler Control and State Register */
#define SCS_SHCSR               (0x24)
/* Configurable Fault Status Register */
#define SCS_CFSR                (0x28)
/* Hard Fault Status Register */
#define SCS_HFSR                (0x2c)
/* Debug Fault Status Register */
#define SCS_DFSR                (0x30)
/* MemManage Fault Address Register */
#define SCS_MMFAR               (0x34)
/* BusFault Address Register */
#define SCS_BFAR                (0x38)
/* Auxiliary Fault Status Register */
#define SCS_AFSR                (0x3c)
/* Offset 0x40 to 0x84 Reserved for CPUID Registers */
/* Coprocessor Access Control Register */
#define SCS_CPACR               (0x88)
/* Floating Point Context Control Register */
#define SCS_FPCCR               (0x134)
/* Floating Point Context Address Register */
#define SCS_FPCAR               (0x138)
/* Floating Point Default Status Control Register */
#define SCS_FPDSCR              (0x13c)
/* Media and FP Feature Register 0 */
#define SCS_MVFR0               (0x140)
/* Media and FP Feature Register 1 */
#define SCS_MVFR1               (0x144)
/* Media and FP Feature Register 2 */
#define SCS_MVFR2               (0x148)

#define SCS_WRITE(OFFS, VALUE)  (*(volatile uint32_t *)((SCS_BASE) + (OFFS))) = (VALUE)
#define SCS_READ(OFFS)          (*(volatile uint32_t *)((SCS_BASE) + (OFFS)))

#endif
