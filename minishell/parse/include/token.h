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
}		t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}		t_token;

// token.c

// Returns a new token element.
// If failed, prints error msg and returns a NULL pointer.
t_token	*init_tk_element(void);

// Free head token and all next elements.
// Set head token to NULL.
void	free_token_list(t_token **ref_head_tk);

#endif