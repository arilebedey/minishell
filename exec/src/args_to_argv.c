/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:12:20 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:12:20 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static int	count_args(t_args *head_arg)
{
	int		count;
	t_args	*curr;

	count = 0;
	curr = head_arg;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char	**args_to_argv(t_args *head_arg)
{
	int		count;
	t_args	*curr;
	char	**argv;
	int		i;

	count = count_args(head_arg);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	curr = head_arg;
	while (curr)
	{
		argv[i] = ft_strdup(curr->value);
		if (!argv[i])
			return (NULL);
		i++;
		curr = curr->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
