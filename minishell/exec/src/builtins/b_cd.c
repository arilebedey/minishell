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

static int	update_env_var(t_env *head_env, const char *key, const char *value)
{
	t_env	*var;

	var = find_env(head_env, key);
	if (!var)
		return (0);
	free(var->value);
	var->value = ft_strdup(value);
	if (!var->value)
	{
		perror("cd: malloc");
		return (1);
	}
	return (0);
}

static int	update_pwd_and_oldpwd(t_env *head_env, const char *oldpwd)
{
	char	*cwd;
	int		ret;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	ret = 0;
	if (oldpwd)
	{
		if (update_env_var(head_env, "OLDPWD", oldpwd))
			ret = 1;
	}
	if (update_env_var(head_env, "PWD", cwd))
		ret = 1;
	free(cwd);
	return (ret);
}

int	builtin_cd(t_command *cmd, t_env *head_env)
{
	t_args	*arg;
	int		argc;
	char	*oldpwd;

	argc = 0;
	arg = cmd->head_arg;
	while (arg)
	{
		argc++;
		arg = arg->next;
	}
	if (argc < 2)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(cmd->head_arg->next->value) != 0)
	{
		perror("cd");
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	if (update_pwd_and_oldpwd(head_env, oldpwd))
	{
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	free(oldpwd);
	g_exit_status = 0;
	return (0);
}
