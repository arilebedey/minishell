/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:09:09 by alebedev          #+#    #+#             */
/*   Updated: 2025/08/09 21:41:48 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free_ast(ms->ast);
		return ;
	}
	if (pid == 0)
	{
		exec_ast(ms, ms->ast);
		exit(1);
	}
	waitpid(pid, &status, 0);
}

void	process_line(t_ms *ms, char *line)
{
	t_token	*tokens;

	add_to_history(line);
	tokens = tokenize_input(line);
	ms->ast = parse_tokens(tokens);
	if (!ms->ast)
	{
		free_tokens(tokens);
		return ;
	}
	execute_in_child(ms);
	free_ast(ms->ast);
	ms->ast = NULL;
}
