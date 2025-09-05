#include "../include/command.h"
#include "../include/env.h"
#include "../include/main.h"
#include "../include/sig/sig.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#define PROMPT "petitshell> "

int	main(int ac, char **av, char **envp)
{
	char				*line;
	static t_env		*head_env = NULL;
	static t_command	*head_cmd = NULL;

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
		free(line);
		if (!exec(head_cmd, head_env) || !init_interactive_sigaction())
			break ;
		free_cmd_list(&head_cmd);
		line = readline(PROMPT);
	}
	return (free_cmd_list(&head_cmd), free_env_list(head_env), 0);
	printf("exit\n");
}
