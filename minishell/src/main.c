#include "../include/command.h"
#include "../include/env.h"
#include "../include/main.h"
#include "../include/sig/sig.h"
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#define PROMPT "petitshell> "

t_env	*g_head_env = NULL;

int	main(int ac, char **av, char **envp)
{
	char				*line;
	static t_env		*head_env = NULL;
	static t_command	*head_cmd = NULL;
	int					exec_result;
	int					sig_result;

	(void)ac;
	(void)av;
	if (!init_interactive_sigaction())
		return (1);
	head_env = init_env_list(envp);
	if (!head_env)
		return (1);
	g_head_env = head_env;
	line = readline(PROMPT);
	while (line)
	{
		add_history(line);
		head_cmd = parse(line, head_env);
		free(line);
		exec_result = exec(head_cmd, head_env);
		sig_result = init_interactive_sigaction();
		free_cmd_list(&head_cmd);
		if (!exec_result || !sig_result)
			break ;
		line = readline(PROMPT);
	}
	ft_printf("exit\n");
	return (free_cmd_list(&head_cmd), free_env_list(head_env), 0);
}
