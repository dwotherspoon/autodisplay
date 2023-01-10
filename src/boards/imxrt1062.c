#include <boards/imxrt1062.h>

/* Linker symbols */
extern unsigned long _stextload;
extern unsigned long _stext;
extern unsigned long _etext;
extern unsigned long _sdataload;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _bss_start;
extern unsigned long _bss_end;
extern unsigned long _flexram_bank_config;
extern unsigned long _stack_top;
extern unsigned long _extram_start;
extern unsigned long _extram_end;
extern unsigned long _flashimagelen;

extern int main();

/* Forward Defs */
void UnhandledInterrupt(void);
void ResetHandler(void);

/* Interrupt vector table */
__attribute__ ((used, aligned(1024), section(".vectorsram")))
void (*volatile _VectorsRam[IMXRT1062_NVIC_NUM_INTERRUPTS + 16])(void);

__attribute__ ((section(".bootdata"), used))
const uint32_t BootData[3] = {
	0x60000000,
	(uint32_t)&_flashimagelen,
	0
};

/* Placeholder for HAB Signature */
__attribute__ ((section(".csf"), used))
const uint32_t hab_csf[768];

/* See i.MX RT1060X Processor Reference Manual - IMXRT1060XRM - p */
__attribute__ ((section(".ivt"), used))
const uint32_t ImageVectorTable[8] = {
	/* Image Header */
	IMXRT1062_IVT_HEADER(0x43, 0x000, 0xD1), 0x432000D1,
	/* Program Entry Point - Use ResetHandler */
	(uint32_t)&ResetHandler,// program entry
	0,			// reserved
	0,			// dcd
	(uint32_t)BootData,	// abs address of boot data
	(uint32_t)ImageVectorTable, // self
	(uint32_t)hab_csf,	// command sequence file
	0			// reserved
};

__attribute__((section(".startup"), optimize("O1")))
static void memory_copy(uint32_t *dest, const uint32_t *src, uint32_t *dest_end) {
	if (dest == src) return;
	while (dest < dest_end) {
		*dest++ = *src++;
	}
}

__attribute__((section(".startup"), optimize("O1")))
static void memory_clear(uint32_t *dest, uint32_t *dest_end) {
	while (dest < dest_end) {
		*dest++ = 0;
	}
}

/* Boot up ResetHandler */
__attribute__((section(".startup"), optimize("no-tree-loop-distribute-patterns")))
void ResetHandler() {
    uint32_t i;
	IMXRT1062_IOMUXC_GPR_WRITE(IMXRT1062_IOMUXC_GPR_GPR17, (uint32_t)&_flexram_bank_config);
	IMXRT1062_IOMUXC_GPR_WRITE(IMXRT1062_IOMUXC_GPR_GPR16, 0x00200007);
	IMXRT1062_IOMUXC_GPR_WRITE(IMXRT1062_IOMUXC_GPR_GPR14, 0x00aa0000);
	__asm__ volatile("mov sp, %0" : : "r" ((uint32_t)&_stack_top) : );
	__asm__ volatile("dsb":::"memory");
	__asm__ volatile("isb":::"memory");

    /* Initialise Memory */

	/* */

	/* Copy instruction data to ITCM */
    memory_copy(&_stext, &_stextload, &_etext);
	/* Copy data to DTCM */
	memory_copy(&_sdata, &_sdataload, &_edata);
	/* Clear BSS */
	memory_clear(&_bss_start, &_bss_end);

	/* Enable FPU - CP10 and CP11 */
	ARM_V7M_SCS_WRITE(ARM_V7M_SCS_CPACR, 0x00f00000);

	/* Initialise interrupt vector table */
	for (i = 0; i < IMXRT1062_NVIC_NUM_INTERRUPTS + 16; i++) {
        _VectorsRam[i] = &UnhandledInterrupt;
    }

	for (i = 0; i < IMXRT1062_NVIC_NUM_INTERRUPTS; i++) {
        ARM_V7M_NVIC_SET_PRIORITY(i, 128);
    }
	
	/* Set Vector Table */
	ARM_V7M_SCS_WRITE(ARM_V7M_SCS_VTOR, (uint32_t)_VectorsRam);

    /* Goto Main */
    main();
	
	/* Wait for interrupt */
	while (1) {
		asm("WFI");
	}
}

void UnhandledInterrupt() {
	while (1) {
		/* Spin */
	}
}
