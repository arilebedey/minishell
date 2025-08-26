#include "../exec/include/exec.h"
#include "../include/command.h"
#include "../include/env.h"
#include "../include/libft.h"
#include "../include/sig.h"
#include "../parse/include/parse.h"
#include <stdio.h>
#include <malloc.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

#define PROMPT "petitshell> "

static int	init_heads(t_command **ref_head_cmd, t_env **ref_head_env);

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
	// TODO: Fonction copiant les variables d'environnement
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

// Initialize heads of command and env list.
// If failed, prints error msg and returns 0.
static int	init_heads(t_command **ref_head_cmd, t_env **ref_head_env)
{
	*ref_head_env = malloc(sizeof(t_env));
	if (!*ref_head_env)
		return (perror("head_env malloc"), 0);
	*ref_head_cmd = malloc(sizeof(t_command));
	if (!*ref_head_cmd)
		return (free(*ref_head_env), perror("head_cmd malloc"), 0);
	(*ref_head_cmd)->args = NULL;
	(*ref_head_cmd)->input_file = NULL;
	(*ref_head_cmd)->output_file = NULL;
	(*ref_head_cmd)->append_mode = 0;
	(*ref_head_cmd)->heredoc_mode = 0;
	(*ref_head_cmd)->heredoc_eof = NULL;
	(*ref_head_cmd)->next = NULL;
	(*ref_head_env)->key = NULL;
	(*ref_head_env)->value = NULL;
	(*ref_head_env)->next = NULL;
	return (1);
}
