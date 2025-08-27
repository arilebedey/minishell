#ifndef HANDLER_H
# define HANDLER_H

// sig_handler.c

// Copy the last signal value received to g_exit_status in shell convention.
void	copy_signal_value(int signum);

// Prints a new line and reset readline buffer.
void	readline_nl(int signum);

#endif
