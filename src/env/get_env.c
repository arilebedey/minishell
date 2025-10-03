/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:53:30 by agense            #+#    #+#             */
/*   Updated: 2025/10/03 13:29:57 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/env.h"

char	*get_env_value(t_env *head_env, const char *key)
{
	t_env	*curr_env;
	size_t	len_key;

	len_key = ft_strlen(key);
	curr_env = head_env;
	while (curr_env)
	{
		if (!ft_strncmp(curr_env->key, key, len_key + 1))
			return (curr_env->value);
		curr_env = curr_env->next;
	}
	return (NULL);
}
