#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
}		t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}		t_token;

// free_token.c

// free the token element given and all next elements.
void	free_token_list(t_token *head_tk);

#endif