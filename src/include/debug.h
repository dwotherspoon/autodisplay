#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef TEST_BUILD
    /* For test mode, map to printf, use stdio */
    #include <stdio.h>
    #define tty_printf(...) printf(...)
    #define __disable_irq() ;
    #define tty_dump_regs() ;
#endif

void dbg_assert(char *msg, char *file, int line);
void dbg_warn(char *msg, char *file, int line);
void dbg_info(char *msg, char *file, int line);
void dbg_error(char *msg, char *file, int line);

#ifdef DEBUG_EN
    #define ASSERT(X, Y)  { if (X) {} else { dbg_assert(Y, __FILE__, __LINE__); } } 
    #define WARN(X, Y)    { if (X) {} else { dbg_warn(Y, __FILE__, __LINE__);   } }
    #define INFO(X)       dbg_info(X, __FILE__, __LINE__);
    #define ERROR(X)	  dbg_error(X, __FILE__, __LINE__);
#else
    #define ASSERT(...) ;
    #define WARN(...)   ;
    #define INFO(...)   ;
    #define ERROR(...)  ;
#endif

#endif