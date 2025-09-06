#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_env	*find_env(t_env *head_env, const char *key)
{
	while (head_env)
	{
		if (!ft_strncmp(head_env->key, key, ft_strlen(key) + 1))
			return (head_env);
		head_env = head_env->next;
	}
	return (NULL);
}

static int	update_pwd_env(t_env *head_env)
{
	char	cwd[4096];
	t_env	*pwd_env;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd");
		return (1);
	}
	pwd_env = find_env(head_env, "PWD");
	if (!pwd_env)
		return (0);
	free(pwd_env->value);
	pwd_env->value = ft_strdup(cwd);
	if (!pwd_env->value)
	{
		perror("cd: malloc");
		return (1);
	}
	return (0);
}

int	builtin_cd(t_command *cmd, t_env *head_env)
{
	t_args	*arg;
	int		argc;

	argc = 0;
	arg = cmd->head_arg;
	while (arg)
	{
		argc++;
		arg = arg->next;
	}
	if (argc < 2)
		return (1);
	if (chdir(cmd->head_arg->next->value) != 0)
	{
		perror("cd");
		g_exit_status = 1;
		return (1);
	}
	if (update_pwd_env(head_env))
	{
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}
