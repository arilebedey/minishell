/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:09:26 by agense            #+#    #+#             */
/*   Updated: 2025/10/02 10:59:38 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/debug.h"
#include "../../include/env.h"
#include "../../libft/libft.h"
#include "../include/parse.h"
#include "../include/token.h"
#include <stdlib.h>

static void	clean_args(t_command *head_cmd);
static void	clean_command_args(t_command *curr_cmd, t_args *curr_arg, \
	t_args *arg_to_free, t_args *next_arg);

t_command	*parse(const char *line, t_env *head_env)
{
	t_token		*head_tk;
	t_command	*head_cmd;

	head_tk = lexer(line);
	if (!head_tk)
		return (NULL);
	debug_token_list(head_tk);
	head_cmd = build_command_list(head_tk);
	free_token_list(&head_tk);
	if (!head_cmd)
		return (NULL);
	if (!expander(head_cmd, head_env))
		return (free_cmd_list(&head_cmd), NULL);
	clean_args(head_cmd);
	debug_command_list(head_cmd);
	return (head_cmd);
}

// Remove empty args for each command
static void	clean_args(t_command *head_cmd)
{
	t_command	*curr_cmd;
	t_args		*curr_arg;
	t_args		*arg_to_free;
	t_args		*next_arg;

	curr_cmd = NULL;
	curr_arg = NULL;
	arg_to_free = NULL;
	next_arg = NULL;
	curr_cmd = head_cmd;
	while (curr_cmd)
	{
		curr_arg = curr_cmd->head_arg;
		if (curr_arg)
			clean_command_args(curr_cmd, curr_arg, arg_to_free, next_arg);
		curr_cmd = curr_cmd->next;
	}
}

// Remove empty args of curr_cmd
static void	clean_command_args(t_command *curr_cmd, t_args *curr_arg, \
	t_args *arg_to_free, t_args *next_arg)
{
	while (!*curr_arg->value)
	{
		arg_to_free = curr_arg;
		curr_arg = curr_arg->next;
		curr_cmd->head_arg = curr_arg;
		free(arg_to_free->value);
		free(arg_to_free);
		if (!curr_arg)
			return ;
	}
	next_arg = curr_arg->next;
	while (curr_arg)
	{
		while (next_arg && !*next_arg->value)
		{
			arg_to_free = next_arg;
			next_arg = next_arg->next;
			free(arg_to_free->value);
			free(arg_to_free);
		}
		curr_arg->next = next_arg;
		curr_arg = curr_arg->next;
		if (curr_arg)
			next_arg = curr_arg->next;
	}
}
