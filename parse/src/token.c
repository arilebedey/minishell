/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:09:18 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:09:18 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/token.h"
#include "../../libft/libft.h"
#include <stdlib.h>

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		return (NULL);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **ref_head_tk, t_token *new_token)
{
	t_token	*curr_tk;

	if (!(*ref_head_tk))
	{
		*ref_head_tk = new_token;
		return ;
	}
	curr_tk = (*ref_head_tk);
	while (curr_tk->next)
		curr_tk = curr_tk->next;
	curr_tk->next = new_token;
}

void	free_token_list(t_token **ref_head_tk)
{
	if (!*ref_head_tk)
		return ;
	if ((*ref_head_tk)->next)
		free_token_list(&(*ref_head_tk)->next);
	free((*ref_head_tk)->value);
	free(*ref_head_tk);
	*ref_head_tk = NULL;
}
