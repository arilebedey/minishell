/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:06:32 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/02 09:04:20 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../libft/libft.h"
#include "../../include/cmd.h"
#include <stdlib.h>
#include <unistd.h>

// Free a NULL-terminated array of strings
static void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// Extract PATH from env list and split it
char	**find_path(t_env *head_env)
{
	const char	*path_value;

	path_value = get_env_value(head_env, "PATH");
	if (!path_value)
		return (NULL);
	return (ft_split(path_value, ':'));
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_str_array(paths), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (free_str_array(paths), NULL);
		if (access(full_path, F_OK) == 0)
		{
			free_str_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

char	*resolve_cmd(char *cmd, t_env *head_env)
{
	char	**paths;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = find_path(head_env);
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
