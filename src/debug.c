#include <stdarg.h>
#include <debug.h>

/* dbg_assert
* Print assert error and stop execution.
*/
void dbg_assert(char *file, int line, char *fmt, ...) {
	va_list args;
	tty_printf("\x1b[31mAssert error: \x1b[93m%s:%d \x1b[0m - ", file, line);
	va_start(args, fmt);
	tty_vprintf(fmt, args);
	va_end(args);
	tty_puts("\r\n");
	tty_dump_regs(); //print registers contents
	__disable_irq(); //disable interrupts
    /* Lock up */
	while (1) {}
}

/* dbg_warn
* Print warn error message.
*/
void dbg_warn(char *file, int line, char *fmt, ...) {
	va_list args;
	tty_printf("\x1b[96mWarning: \x1b[93m%s:%d \x1b[0m - ", file, line);
	va_start(args, fmt);
	tty_vprintf(fmt, args);
	va_end(args);
	tty_puts("\r\n");
}

/* dbg_info
 * Print debug information message.
*/
void dbg_info(char *file, int line, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
    tty_printf("Info: %s:%d - ", file, line);
	va_start(args, fmt);
	tty_vprintf(fmt, args);
	va_end(args);
	tty_puts("\r\n");
}

/* dbg_throw
* Print error and stop execution.
*/
void dbg_error(char *file, int line, char *fmt, ...) {
	va_list args;
	tty_printf("\x1b[31mError thrown: \x1b[93m%s:%d \x1b[0m - ", file, line);
	va_start(args, fmt);
	tty_vprintf(fmt, args);
	va_end(args);
	tty_puts("\r\n");
	__disable_irq(); //disable interrupts
    /* Lock up */
	while (1) {}
}
