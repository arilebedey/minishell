/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:09:26 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:09:26 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/debug.h"
#include "../../include/env.h"
#include "../../libft/libft.h"
#include "../include/parse.h"
#include "../include/token.h"

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
	debug_command_list(head_cmd);
	return (head_cmd);
}
