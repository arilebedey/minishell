#ifndef SIG_H
# define SIG_H

# include <signal.h>

# define CONV_SIGINT 128 + SIGINT
# define CONV_SIGTERM 128 + SIGTERM
# define CONV_SIGQUIT 128 + SIGQUIT

extern volatile sig_atomic_t	g_exit_status;

// interactive_sig.c

// Initialize signals for interactive mode.
// If failed, prints error msg and returns 0.
int	init_interactive_sigaction(void);

// process_sig.c

// Initialize signals for parent process on fork.
// If failed, prints error msg and returns 0.
int	init_parent_sigaction(void);
// Initialize signals for child process on fork.
// If failed, prints error msg and returns 0.
int	init_child_sigaction(void);

#endif
