/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:21:27 by alebedev          #+#    #+#             */
/*   Updated: 2025/08/09 21:39:48 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_ms(t_ms *ms, t_token *tokens)
{
	if (tokens)
		free_tokens(tokens);
	if (ms->ast)
	{
		free_ast(ms->ast);
		ms->ast = NULL;
	}
}

void	exit_shell(t_ms *ms, t_token *tokens, int status)
{
	cleanup_ms(ms, tokens);
	rl_clear_history();
	exit(status);
}

void	free_ast(t_tree *r)
{
	if (!r)
		return ;
	free_ast(r->left);
	free_ast(r->right);
	if (r->tok)
	{
		free(r->tok->text);
		free(r->tok);
	}
	free(r);
}
