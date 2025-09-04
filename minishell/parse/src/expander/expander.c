#include "../../../include/sig/sig.h"
#include "../../../include/command.h"
#include "../../../include/error.h"
#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/expander.h"
#include <stdlib.h>
#include <stdio.h>

static int	remove_quotes(void *curr_elem, t_quotes quote);
static int	expansion(void *curr_elem, char **out_value, t_env *head_env);
static int	args_expansion(t_command *curr_cmd, t_env *head_env);
static int	files_expansion(t_command *curr_cmd, t_env *head_env);

int	expander(t_command *head_cmd, t_env *head_env)
{
	t_command	*curr_cmd;

	curr_cmd = head_cmd;
	while (curr_cmd)
	{
		if (!args_expansion(curr_cmd, head_env))
			return (0);
		if (!files_expansion(curr_cmd, head_env))
			return (0);
		curr_cmd = curr_cmd->next;
	}
	return (1);
}

// Expansion for args elements in current command.
// If failed, prints error msg and returns 0.
static int	args_expansion(t_command *curr_cmd, t_env *head_env)
{
	t_args		*curr_arg;

	curr_arg = curr_cmd->head_arg;
	while (curr_arg)
	{
		if (!expansion(curr_arg, &curr_arg->value, head_env))
			return (0);
		curr_arg = curr_arg->next;
	}
	return (1);
}

// Expansion for files elements in current command.
// If failed, prints error msg and returns 0.
static int	files_expansion(t_command *curr_cmd, t_env *head_env)
{
	t_infile	*curr_infile;
	t_outfile	*curr_outfile;

	curr_infile = curr_cmd->head_infile;
	while (curr_infile)
	{
		if (!expansion(curr_infile, &curr_infile->value, head_env))
			return (0);
		curr_infile = curr_infile->next;
	}
	curr_outfile = curr_cmd->head_outfile;
	while (curr_outfile)
	{
		if (!expansion(curr_outfile, &curr_outfile->value, head_env))
			return (0);
		curr_outfile = curr_outfile->next;
	}
	return (1);
}

// Expand the value of the curr_elem given.
// If failed, prints error msg and returns 0.
static int	expansion(void *curr_elem, char **out_value, t_env *head_env)
{
	if (**out_value == S_QUOTE)
	{
		if (!remove_quotes(curr_elem, S_QUOTE))
			return (0);
	}
	else if (**out_value == D_QUOTE)
	{
		if (!remove_quotes(curr_elem, D_QUOTE))
			return (0);
		if (ft_strchr(*out_value, '$'))
		{
			if (!handle_env_variables(out_value, head_env))
				return (0);
		}
	}
	else if (ft_strchr(*out_value, '$'))
	{
		if (!handle_env_variables(out_value, head_env))
			return (0);
	}
	return (1);
}

// Remove the quotes of curr_arg/infile/outfile.
// (No check done at start, be sure curr_arg is quotes argument.)
// If failed, prints error msg and returns 0.
static int	remove_quotes(void *curr_elem, t_quotes quote)
{
	char	*tmp_value;
	char	**ref_value;

	ref_value = (char **)curr_elem;
	tmp_value = ft_strdup(*ref_value);
	if (!tmp_value)
		return (perror("tmp_value strdup"), 0);
	free(*ref_value);
	*ref_value = ft_strndup(tmp_value + 1, \
		ft_strlen2(tmp_value + 1, quote));
	free(tmp_value);
	if (!*ref_value)
		return (perror("curr_arg value strndup"), 0);
	return (1);
}

