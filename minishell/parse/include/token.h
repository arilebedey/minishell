/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:08:29 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:08:29 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

// token.c

// Returns a new token.
// If failed, returns NULL
t_token				*create_token(char *value, t_token_type type);

// Add new token to the list
void				add_token(t_token **ref_head_tk, t_token *new_token);

// Free head token and all next elements.
// Set head token to NULL.
void				free_token_list(t_token **ref_head_tk);

#endif
