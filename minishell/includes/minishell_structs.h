#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_OUT,
}			t_token_type;

/* text: word text or operator symbol */
typedef struct s_token
{
	t_token_type	type;
	char			*text;
	struct s_token	*next;
}				t_token;

/* Abstract Syntax Tree node */
typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	t_token			*tok;
	char			**argv;
}				t_node;

typedef struct s_ms
{
	t_node	*ast;
	char	**env;
}				t_ms;

#endif
