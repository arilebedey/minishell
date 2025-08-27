#include "../../libft/libft.h"
#include "../../include/sig/handler.h"
#include <signal.h>
#include <stdio.h>

int	init_parent_sigaction(void)
{
	struct sigaction	sa_restart;

	sigemptyset(&sa_restart.sa_mask);
	sa_restart.sa_flags = SA_RESTART;
	sa_restart.sa_handler = &copy_signal_value;
	if (sigaction(SIGINT, &sa_restart, NULL) == -1)
		return (perror("sigaction sigint error"), 0);
	if (sigaction(SIGTERM, &sa_restart, NULL) == -1)
		return (perror("sigaction sigterm error"), 0);
	if (sigaction(SIGQUIT, &sa_restart, NULL) == -1)
		return (perror("sigaction sigquit error"), 0);
	return (1);
}

int	init_child_sigaction(void)
{
	struct sigaction	sa_default;

	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sa_default.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa_default, NULL) == -1)
		return (perror("sigaction sigint error"), 0);
	if (sigaction(SIGTERM, &sa_default, NULL) == -1)
		return (perror("sigaction sigterm error"), 0);
	if (sigaction(SIGQUIT, &sa_default, NULL) == -1)
		return (perror("sigaction sigquit error"), 0);
	return (1);
}
