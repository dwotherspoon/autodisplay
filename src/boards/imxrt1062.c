#include <stdint.h>
#include <boards/imxrt1062.h>

extern unsigned long _stextload;
extern unsigned long _stext;
extern unsigned long _etext;
extern unsigned long _sdataload;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _flexram_bank_config;
extern unsigned long _estack;
extern unsigned long _extram_start;
extern unsigned long _extram_end;
extern unsigned long _flashimagelen;

extern int main();

/* Forward Defs */
void UnhandledInterrupt(void);
void ResetHandler(void);

__attribute__ ((used, aligned(1024), section(".vectorsram")))
void (* volatile _VectorsRam[NVIC_NUM_INTERRUPTS+16])(void);


__attribute__ ((section(".bootdata"), used))
const uint32_t BootData[3] = {
	0x60000000,
	(uint32_t)&_flashimagelen,
	0
};

__attribute__ ((section(".csf"), used))
const uint32_t hab_csf[768];	// placeholder for HAB signature


__attribute__ ((section(".ivt"), used))
const uint32_t ImageVectorTable[8] = {
	0x432000D1,		// header
	(uint32_t)&ResetHandler,// program entry
	0,			// reserved
	0,			// dcd
	(uint32_t)BootData,	// abs address of boot data
	(uint32_t)ImageVectorTable, // self
	(uint32_t)hab_csf,	// command sequence file
	0			// reserved
};


/* Boot up ResetHandler */
__attribute__((section(".startup"), optimize("no-tree-loop-distribute-patterns")))
void ResetHandler() {
    uint32_t i;
	IOMUXC_GPR_GPR17 = (uint32_t)&_flexram_bank_config;
	IOMUXC_GPR_GPR16 = 0x00200007;
	IOMUXC_GPR_GPR14 = 0x00AA0000;
	__asm__ volatile("mov sp, %0" : : "r" ((uint32_t)&_estack) : );
	__asm__ volatile("dsb":::"memory");
	__asm__ volatile("isb":::"memory");

    /* Initalise Memory */
    memory_copy(&_stext, &_stextload, &_etext);
	memory_copy(&_sdata, &_sdataload, &_edata);
	memory_clear(&_sbss, &_ebss);


	/* Enable FPU - CP10 and CP11 */
	SCS_WRITE(SCS_CPACR, 0x00F00000);

	// Setup new interrupt & exception vector table
	for (i=0; i < NVIC_NUM_INTERRUPTS + 16; i++) {
        _VectorsRam[i] = &UnhandledInterrupt;
    }
	for (i=0; i < NVIC_NUM_INTERRUPTS; i++) {
        NVIC_SET_PRIORITY(i, 128);
    }
	
	SCS_WRITE(SCS_VTOR, (uint32_t)_VectorsRam);

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