#include "../include/env.h"
#include "../include/command.h"
#include "../libft/libft.h"
#include <malloc.h>

static int	get_first_equal_index(char *s);

int	init_heads(t_command **ref_head_cmd, t_env **ref_head_env)
{
	*ref_head_env = malloc(sizeof(t_env));
	if (!*ref_head_env)
		return (perror("head_env malloc"), 0);
	*ref_head_cmd = malloc(sizeof(t_command));
	if (!*ref_head_cmd)
		return (free(*ref_head_env), perror("head_cmd malloc"), 0);
	(*ref_head_cmd)->args = NULL;
	(*ref_head_cmd)->input_file = NULL;
	(*ref_head_cmd)->output_file = NULL;
	(*ref_head_cmd)->append_mode = 0;
	(*ref_head_cmd)->heredoc_mode = 0;
	(*ref_head_cmd)->heredoc_eof = NULL;
	(*ref_head_cmd)->next = NULL;
	(*ref_head_env)->key = NULL;
	(*ref_head_env)->value = NULL;
	(*ref_head_env)->next = NULL;
	return (1);
}

int	init_env_list(char **envp, t_env *head_env)
{
	int		i;
	int		first_equal_index;
	t_env	*current_env;

	i = -1;
	current_env = head_env;
	while (envp[++i])
	{
		first_equal_index = get_first_equal_index(envp[i]);
		current_env->key = ft_substr(envp[i], 0, first_equal_index);
		current_env->value = ft_substr(envp[i], first_equal_index + 1, \
			ft_strlen(envp[i] + first_equal_index + 1));
		if (envp[i + 1])
		{
			current_env->next = malloc(sizeof(t_env));
			if (!current_env->next)
				return (free_env_list(head_env), 0);
			current_env = current_env->next;
		}
	}
	current_env->next = NULL;
	return (1);
}

// Returns the index of the first '=' in the string s
// Returns -1 if no '=' have been found
static int	get_first_equal_index(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (-1);
}
