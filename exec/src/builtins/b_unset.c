/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:22:01 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 08:26:00 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include <stdlib.h>

static void	remove_env_var(t_env **head_env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!head_env || !*head_env || !key)
		return ;
	curr = *head_env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(curr->key) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head_env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	builtin_unset(t_command *cmd, t_env **head_env)
{
	t_args	*arg;

	arg = cmd->head_arg;
	if (arg)
		arg = arg->next;
	while (arg)
	{
		remove_env_var(head_env, arg->value);
		arg = arg->next;
	}
	g_exit_status = 0;
	return (0);
}
