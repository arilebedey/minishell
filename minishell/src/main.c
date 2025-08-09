/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:03:30 by alebedev          #+#    #+#             */
/*   Updated: 2025/08/09 21:27:56 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_ms(t_ms *ms, char **env)
{
	ms->env = env;
	ms->ast = NULL;
}

static void	run_shell(t_ms *ms)
{
	char	*line;

	line = readline("$ ");
	while (line)
	{
		process_line(ms, line);
		line = readline("$ ");
	}
	// Ctrl+D exit ?
	exit_shell(ms, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	init_ms(&ms, env);
	run_shell(&ms);
	return (0);
}
