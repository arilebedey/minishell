#include "../../libft/libft.h"
#include "../../include/sig/handler.h"
#include <signal.h>
#include <stdio.h>

volatile sig_atomic_t	g_exit_status = 0;

int	init_interactive_sigaction(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_term;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = &readline_nl;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (perror("sigaction sigint error"), 0);
	sigemptyset(&sa_term.sa_mask);
	sa_term.sa_flags = 0;
	sa_term.sa_handler = &copy_signal_value;
	if (sigaction(SIGTERM, &sa_term, NULL) == -1)
		return (perror("sigaction sigterm error"), 0);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (perror("sigaction sigquit error"), 0);
	return (1);
}
