/* dbg_assert
* Print assert error and stop execution.
*/
void dbg_assert(char * msg, char * file, int line) {
	tty_printf("\x1b[31mAssert error: \x1b[93m%s:%d \x1b[0m - %s\r\n", file, line, msg);
	tty_dump_regs(); //print registers contents
	__disable_irq(); //disable interrupts
    /* Lock up */
	while (1) {}
}

/* dbg_warn
* Print warn error message.
*/
void dbg_warn(char *msg, char *file, int line) {
	tty_printf("\x1b[96mWarning: \x1b[93m%s:%d \x1b[0m - %s\r\n", file, line, msg);
}

/* dbg_info
 * Print debug information message.
*/
void dbg_info(char *msg, char *file, int line) {
    tty_printf("Info: %s:%d - %s\n\r", file, line , msg);
}

/* dbg_throw
* Print error and stop execution.
*/
void dbg_error(char * msg, char * file, int line) {
	tty_printf("\x1b[31mError thrown: \x1b[93m%s:%d \x1b[0m - %s\r\n", file, line, msg);
	__disable_irq(); //disable interrupts
    /* Lock up */
	while (1) {}
}