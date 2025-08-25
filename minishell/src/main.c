#include "../include/parse/parse.h"
#include "../include/exec/exec.h"
#include "../include/env.h"
#include "../include/command.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <malloc.h>

#define PROMPT "petitshell> "

// TODO: Reorganiser les fichiers
int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env		*head_env;
	t_command	*head_cmd;

	if (ac || av || envp)
	{

	}
	head_env = malloc(sizeof(t_env));
	if (!head_env)
		return (perror("head_env malloc"), 1);
	head_cmd = malloc(sizeof(t_command));
	if (!head_cmd)
		return (perror("head_cmd malloc"), 1);
	head_cmd->args = NULL;
	head_cmd->input_file = NULL;
	head_cmd->output_file = NULL;
	head_cmd->heredoc_eof = NULL;
	head_cmd->next = NULL;
	head_env->value = NULL;
	head_env->next = NULL;
	// TODO: Gestion des signaux
	// TODO: Fonction copiant les variables d'environnement
	line = readline(PROMPT);
	while (line)
	{
		if (!parse(line, head_cmd, head_env))
			return (free(line), 1);
		if (!exec(head_cmd, head_env))
			return (free(line), 1);
		free(line);
		line = readline(PROMPT);
	}
	rl_clear_history();
	free_env_list(head_env);
	free_cmd_list(head_cmd);
	return (0);
}

