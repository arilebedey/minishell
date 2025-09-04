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
	const char	*env_v;
	char		*tmp_v;
}		t_handle_env;

// replace.c

// Replace env keys by its values.
// If failed, prints error msg and returns 0.
int	handle_env_variables(char **out_value, t_env *head_env);

#endif
