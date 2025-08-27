#include "../include/main.h"
#include "../include/command.h"
#include "../include/env.h"
#include "../libft/libft.h"
#include "../include/sig/sig.h"
#include <malloc.h>
#include <readline/history.h>
#include <readline/readline.h>

#define PROMPT "petitshell> "

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env		*head_env;
	t_command	*head_cmd;

	(void)ac;
	(void)av;
	if (!init_interactive_sigaction())
		return (1);
	head_env = init_env_list(envp);
	if (!head_env)
		return (1);
	line = readline(PROMPT);
	while (line)
	{
		add_history(line);
		head_cmd = parse(line, head_env);
		if (!head_cmd)
			return (free(line), free_env_list(head_env), 1);
		if (!exec(head_cmd, head_env))
			return (free(line), free_cmd_list(head_cmd), \
				free_env_list(head_env), 1);
		free_cmd_list(head_cmd);
		free(line);
		if (!init_interactive_sigaction())
			break ;
		line = readline(PROMPT);
	}
	free_env_list(head_env);
	return (0);
}
