#ifndef SIG_H
# define SIG_H

#include <stdio.h>
# include <signal.h>
#include <readline/readline.h>

# define CONV_SIGINT 128 + SIGINT
# define CONV_SIGQUIT 128 + SIGQUIT
# define CONV_SIGTERM 128 + SIGTERM

extern volatile sig_atomic_t	g_exit_status;

// interactive_sig.c

// Initialize signals for interactive mode.
// Can be called multiple times for updating.
// If failed, prints error msg and returns 0.
int	init_interactive_sigaction(void);

#endif
