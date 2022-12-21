#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef TEST_BUILD
    /* For test mode, map to printf, use stdio */
    #include <stdio.h>
    #define tty_printf(...) printf(__VA_ARGS__)
    #define tty_vprintf(...) vprintf(__VA_ARGS__)
    #define tty_puts(X)     puts(X)
    #define __disable_irq() ;
    #define tty_dump_regs() ;
#endif

void dbg_assert(char *file, int line, char *fmt, ...);
void dbg_warn(char *file, int line, char *fmt, ...);
void dbg_info(char *file, int line, char *fmt, ...);
void dbg_error(char *file, int line, char *fmt, ...);

#ifdef DEBUG_EN
    #define ASSERT(COND, ...)  { if (!(COND)) { dbg_assert(__FILE__, __LINE__, __VA_ARGS__); } } 
    #define WARN(COND, ...)    { if (!(COND)) { dbg_warn(__FILE__, __LINE__, __VA_ARGS__); } }
    #define INFO(...)          dbg_info(__FILE__, __LINE__, __VA_ARGS__);
    #define ERROR(...)	       dbg_error(__FILE__, __LINE__, __VA_ARGS__);
#else
    #define ASSERT(...) ;
    #define WARN(...)   ;
    #define INFO(...)   ;
    #define ERROR(...)  ;
#endif

#endif
