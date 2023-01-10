#ifndef _ARM_V7M_H
#define _ARM_V7M_H

#include <stdint.h>

#define ARMV7M_IRQ_MEMMANAGE -1

/* Arm V7M Architecture Reference Manual DDI0403E, B3.2.2, p595 */
#define ARM_V7M_SCS_BASE                (0xe000ed00)
/* CPUID Base Register */
#define ARM_V7M_SCS_CPUID               (0x0)
/* Interrupt Control and State Register */
#define ARM_V7M_SCS_ICSR                (0x4)
/* Vector Table Offset Register */
#define ARM_V7M_SCS_VTOR                (0x8)
/* Application Interrupt and Reset Control Register */
#define ARM_V7M_SCS_AIRCR               (0xc)
/* System Control Register */
#define ARM_V7M_SCS_SCR                 (0x10)
/* Configuration and Control Register */
#define ARM_V7M_SCS_CCR                 (0x14)
/* System Handler and Priority Register 1 */
#define ARM_V7M_SCS_SHPR1               (0x18)
/* System Handler and Priority Register 2 */
#define ARM_V7M_SCS_SHPR2               (0x1c)
/* System Handler and Priority Register 3 */
#define ARM_V7M_SCS_SHPR3               (0x20)
/* System Handler Control and State Register */
#define ARM_V7M_SCS_SHCSR               (0x24)
/* Configurable Fault Status Register */
#define ARM_V7M_SCS_CFSR                (0x28)
/* Hard Fault Status Register */
#define ARM_V7M_SCS_HFSR                (0x2c)
/* Debug Fault Status Register */
#define ARM_V7M_SCS_DFSR                (0x30)
/* MemManage Fault Address Register */
#define ARM_V7M_SCS_MMFAR               (0x34)
/* BusFault Address Register */
#define ARM_V7M_SCS_BFAR                (0x38)
/* Auxiliary Fault Status Register */
#define ARM_V7M_SCS_AFSR                (0x3c)
/* Offset 0x40 to 0x84 Reserved for CPUID Registers */
/* Coprocessor Access Control Register */
#define ARM_V7M_SCS_CPACR               (0x88)
/* Floating Point Context Control Register */
#define ARM_V7M_SCS_FPCCR               (0x134)
/* Floating Point Context Address Register */
#define ARM_V7M_SCS_FPCAR               (0x138)
/* Floating Point Default Status Control Register */
#define ARM_V7M_SCS_FPDSCR              (0x13c)
/* Media and FP Feature Register 0 */
#define ARM_V7M_SCS_MVFR0               (0x140)
/* Media and FP Feature Register 1 */
#define ARM_V7M_SCS_MVFR1               (0x144)
/* Media and FP Feature Register 2 */
#define ARM_V7M_SCS_MVFR2               (0x148)

#define ARM_V7M_SCS_WRITE(OFFS, VALUE)  (*(volatile uint32_t *)((ARM_V7M_SCS_BASE) + (OFFS))) = (VALUE)
#define ARM_V7M_SCS_READ(OFFS)          (*(volatile uint32_t *)((ARM_V7M_SCS_BASE) + (OFFS)))

/* Arm V7M Architecture Reference Manual DDI0403E, B3.4.3, p626 */
#define ARM_V7M_NVIC_BASE 0xe000e400
/* Interrupt Set-Enable Registers - NVIC_ISER0-15 (0x00 - 0x3c) */
#define ARM_V7M_NVIC_ISER 0x000
/* Interrupt Clear-Enable Registers - NVIC_ICER0-15 (0x80 - 0xbc) */
#define ARM_V7M_NVIC_ICER 0x080
/* Interrupt Set-Pending Registers - NVIC_ISPR0-15 (0x100 - 0x13c) */
#define ARM_V7M_NVIC_ISPR 0x100
/* Interrupt Clear-Pending Registers - NVIC_ICPR0-15 (0x180 - 0x1bc) */
#define ARM_V7M_NVIC_ICPR 0x180
/* Interrupt Active-Bit Registers - NVIC_IABR0-15 (0x200 - 0x23c) */
#define ARM_V7M_NVIC_IABR 0x200
/* Interrupt Priority Registers - NVIC_IPR0-123 (0x300 - 0x4ec) */
#define ARM_V7M_NVIC_IPR  0x300

#define ARM_V7M_NVIC_SET_PRIORITY(IRQ, PRI) (*(volatile uint8_t *)((ARM_V7M_NVIC_BASE) + (ARM_V7M_NVIC_IPR) + (IRQ))) = (PRI)
#define ARM_V7M_NVIC_GET_PRIORITY(IRQ)      (*(volatile uint8_t *)((ARM_V7M_NVIC_BASE) + (ARM_V7M_NVIC_IPR) + (IRQ)))

#endif
