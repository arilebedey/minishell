#include "../includes/minishell.h"

static void	add_to_history(char *line)
{
	if (*line)
		add_history(line);
}

static t_token	*tokenize_input(char *line)
{
	t_token	*tokens;

	tokens = lexer(line);
	free(line);
	return (tokens);
}

static t_tree	*parse_tokens(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (build_ast(tokens));
}

static void	execute_in_child(t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exec_ast(ms, ms->ast);
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
}

void	process_line(t_ms *ms, char *line)
{
	t_token	*head;

	add_to_history(line);
	head = tokenize_input(line);
	if (syntax_error(head))
	{
		free_tokens(head);
		/* ms->last_status = 2; // if you track it */
		return ;
	}
	ms->ast = parse_tokens(head);
	if (!ms->ast)
	{
		free_tokens(head);
		return ;
	}
	execute_in_child(ms);
	free_ast(ms->ast);
	ms->ast = NULL;
}
