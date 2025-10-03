/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:06:35 by agense            #+#    #+#             */
/*   Updated: 2025/10/03 13:29:53 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// Return a pointer to a new env linked list.
// If failed, prints error msg and returns 0.
t_env				*init_env_list(char **envp);
// Returns the value corresponding to the key (no dup).
// If the key does not exist, returns NULL pointer.
char				*get_env_value(t_env *head_env, const char *key);
// Free all env elements.
void				free_env_list(t_env *head_env);

#endif
