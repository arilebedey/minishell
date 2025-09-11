#include "../include/command.h"
#include "../include/env.h"
#include "../include/main.h"
#include "../include/sig/sig.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

#define PROMPT "\001\033[1;32m\002🥸 💻 petitshell> "

static int	run_shell_loop(t_env **head_env);

int	main(int ac, char **av, char **envp)
{
	static t_env	*head_env = NULL;

	(void)ac;
	(void)av;
	if (!init_interactive_sigaction())
		return (1);
	head_env = init_env_list(envp);
	if (!head_env)
		return (1);
	if (!run_shell_loop(&head_env))
		ft_printf("exit\n");
	return (free_env_list(head_env), 0);
}

static int	run_shell_loop(t_env **head_env)
{
	char		*line;
	t_command	*head_cmd;
	int			exec_result;
	int			sig_result;

	line = readline(PROMPT);
	while (line)
	{
		add_history(line);
		head_cmd = parse(line, *head_env);
		free(line);
		exec_result = exec(head_cmd, *head_env);
		sig_result = init_interactive_sigaction();
		free_cmd_list(&head_cmd);
		if (!exec_result || !sig_result)
			return (0);
		line = readline(PROMPT);
	}
	return (1);
}
