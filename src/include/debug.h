#ifndef _DEBUG_H
#define _DEBUG_H

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