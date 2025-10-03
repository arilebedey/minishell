/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:08:21 by agense            #+#    #+#             */
/*   Updated: 2025/10/03 13:29:32 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef enum e_quotes
{
	S_QUOTE = '\'',
	D_QUOTE = '\"'
}		t_quotes;

typedef struct s_handle_env
{
	char		*curs;
	char		*bk;
	char		*ak;
	char		*key;
	int			is_exit_status;
	char		*env_v;
	char		*tmp_v;
}		t_handle_env;

// replace.c

// Replace env keys by its values.
// If failed, prints error msg and returns 0.
int	handle_env_variables(char **out_value, t_env *head_env);

#endif
