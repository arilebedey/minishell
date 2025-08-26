#include "../../include/sig.h"
#include "../../include/libft.h"
#include <readline/readline.h>
#include <signal.h>

volatile sig_atomic_t	g_exit_status = 0;

static void	sigint_interactive_handler(void);
static void	interactive_signal_handler(int signum);

int	init_interactive_sigaction(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_term;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART; // to restart blocking functions (like readline or waitpid) instead of stopping them.
	sa_int.sa_handler = &interactive_signal_handler;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (perror("sigaction sigint error"), 0);
	sigemptyset(&sa_term.sa_mask);
	sa_term.sa_flags = 0;
	sa_term.sa_handler = &interactive_signal_handler;
	if (sigaction(SIGTERM, &sa_term, NULL) == -1)
		return (perror("sigaction sigterm error"), 0);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (perror("sigaction sigquit error"), 0);
	return (1);
}

// Copy the signal value received to g_exit_status in shell convention.
// Go to a new line if SIGINT was sent.
static void	interactive_signal_handler(int signum)
{
	g_exit_status = 128 + signum;
	if (g_exit_status == CONV_SIGINT)
		sigint_interactive_handler();
}
// Prints a new line and reset readline buffer.
static void	sigint_interactive_handler(void)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
