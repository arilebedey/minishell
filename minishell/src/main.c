#include "../parse/include/parse.h"
#include "../exec/include/exec.h"
#include "../include/command.h"
#include "../include/env.h"
#include "../include/sig/sig.h"
#include "../include/init.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <malloc.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

#define PROMPT "petitshell> "

int	main(int ac, char **av, char **envp)
{
	char				*line;
	static t_env		*head_env = NULL;
	static t_command	*head_cmd = NULL;

	if (ac || av || envp)
	{
	}
	if (!init_interactive_sigaction())
		return (1);
	if (!init_heads(&head_cmd, &head_env))
		return (1);
	if (!init_env_list(envp, head_env))
		return (free_cmd_list(head_cmd), 1);
	line = readline(PROMPT);
	while (line)
	{
		add_history(line);
		if (!parse(line, head_cmd, head_env))
			return (free(line), 1);
		if (!exec(head_cmd, head_env))
			return (free(line), 1);
		free(line);
		if (!init_interactive_sigaction())
			break ;
		line = readline(PROMPT);
	}
	rl_clear_history();
	free_env_list(head_env);
	free_cmd_list(head_cmd);
	return (0);
}
