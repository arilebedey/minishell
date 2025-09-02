#include "../../../include/sig/sig.h"
#include "../../../include/command.h"
#include "../../../include/error.h"
#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/expander.h"
#include <stdlib.h>
#include <stdio.h>

static int	remove_quotes(t_args *curr_arg, t_quotes quote);
static char	*get_expanded_value(char **split_arg, t_env *head_env, \
	int is_first_an_env_var);
static int	handle_env_arg(t_args *curr_arg, t_env *head_env);
void		free_split(char **split_s);

// TODO: se retaper handle_env_arg a cause des espaces de morts :)))
// il faut check les caracteres de la cle jusqu'a un espace, un $ ou eof.
// + leaks randoms
int	expander(t_command *head_cmd, t_env *head_env)
{
	t_command	*curr_cmd;
	t_args		*curr_arg;

	curr_cmd = head_cmd;
	while (curr_cmd)
	{
		curr_arg = curr_cmd->head_arg;
		while (curr_arg)
		{
			if (*(curr_arg->value) == S_QUOTE)
			{
				if (!remove_quotes(curr_arg, S_QUOTE))
					return (0);
			}
			else if (*(curr_arg->value) == D_QUOTE)
			{
				if (!remove_quotes(curr_arg, D_QUOTE))
					return (0);
				if (ft_strchr(curr_arg->value, '$'))
				{
					if (!handle_env_arg(curr_arg, head_env))
						return (0);
				}
			}
			else if (ft_strchr(curr_arg->value, '$'))
			{
				if (!handle_env_arg(curr_arg, head_env))
					return (0);
			}
			curr_arg = curr_arg->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (1);
}

// Remove the quotes of curr_arg. Precise which one in quote argument.
// (No check done at start, be sure curr_arg is quotes argument.)
// If failed, prints error msg and returns 0.
static int	remove_quotes(t_args *curr_arg, t_quotes quote)
{
	char	*tmp_value;

	tmp_value = ft_strdup(curr_arg->value);
	if (!tmp_value)
		return (perror("tmp_value strdup"), 0);
	free(curr_arg->value);
	curr_arg->value = ft_strndup(tmp_value + 1, \
		ft_strlen2(tmp_value + 1, quote));
	free(tmp_value);
	if (!curr_arg->value)
		return (perror("curr_arg value strndup"), 0);
	return (1);
}

// Replace env keys by its values.
// If failed, prints error msg and returns 0.
static int	handle_env_arg(t_args *curr_arg, t_env *head_env)
{
	char	**split_arg;
	int		is_first_an_env_var;

	is_first_an_env_var = 0;
	if (*(curr_arg->value) == '$')
		is_first_an_env_var = 1;
	split_arg = ft_split(curr_arg->value, '$');
	if (!split_arg)
		return (perror("handle_env_arg split"), 0);
	free(curr_arg->value);
	curr_arg->value = get_expanded_value(split_arg, head_env, is_first_an_env_var);
	free_split(split_arg);
	if (!curr_arg->value)
		return (perror("expansion"), 0);
	return (1);
}

// Expands all values in split_arg, joins all of them in a string a returns this string.
// If failed, returns NULL pointer.
static char	*get_expanded_value(char **split_arg, t_env *head_env, \
	int is_first_an_env_var)
{
	char	*expanded_value;
	char	*tmp_exp_value;
	char	*env_value;
	int		i;

	i = -1;
	if (!is_first_an_env_var)
	{
		expanded_value = ft_strdup(split_arg[0]);
		if (!expanded_value)
			return (NULL);
	}
	else
	{
		expanded_value = malloc(1);
		if (!expanded_value)
			return (NULL);
		*expanded_value = 0;
	}
	//TODO: SUPP LES ESPACES ENTRE LES ENV VAR
	//TODO: le cas $?
	while (split_arg[++i])
	{
		env_value = get_env_value(head_env, split_arg[i]);
		tmp_exp_value = ft_strdup(expanded_value);
		if (!tmp_exp_value)
			return (free(env_value), free(expanded_value), NULL);
		free(expanded_value);
		if (env_value)
			expanded_value = ft_strjoin(tmp_exp_value, env_value);
		else
			expanded_value = ft_strjoin(tmp_exp_value, "\0");
		free(tmp_exp_value);
		if (!expanded_value)
			return (NULL);
	}
	return (expanded_value);
}

// Free pointer to pointer of char.
void	free_split(char **split_s)
{
	int	i;

	i = -1;
	while (split_s[++i])
		free(split_s[i]);
	free(split_s);
}
