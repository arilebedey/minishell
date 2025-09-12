/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:08:36 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:10:19 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	save_stdin_fd(void)
{
	int	save_stdin;

	save_stdin = dup(STDIN_FILENO);
	if (save_stdin < 0)
	{
		perror("dup stdin");
		return (-1);
	}
	return (save_stdin);
}

static int	setup_heredoc_sigaction(struct sigaction *orig_int)
{
	struct sigaction	act_int;

	if (sigaction(SIGINT, NULL, orig_int) == -1)
		return (perror("sigaction"), -1);
	act_int = *orig_int;
	act_int.sa_handler = heredoc_sigint;
	act_int.sa_flags |= SA_RESTART;
	sigemptyset(&act_int.sa_mask);
	if (sigaction(SIGINT, &act_int, NULL) == -1)
		return (perror("sigaction heredoc"), -1);
	return (0);
}

static void	restore_context(int save_stdin, struct sigaction *orig_int)
{
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	sigaction(SIGINT, orig_int, NULL);
}

static void	read_heredoc_lines(t_infile *infile, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, infile->value, ft_strlen(infile->value) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	write_heredoc_to_fd(t_infile *infile, int fd, char *tmpname,
		t_command *head_cmd)
{
	struct sigaction	orig_int;
	int					save_stdin;

	(void)tmpname;
	(void)head_cmd;
	g_exit_status = 0;
	save_stdin = save_stdin_fd();
	if (save_stdin < 0)
		return (0);
	if (setup_heredoc_sigaction(&orig_int) == -1)
		return (close(save_stdin), 0);
	read_heredoc_lines(infile, fd);
	restore_context(save_stdin, &orig_int);
	if (g_exit_status == 130)
		return (0);
	return (1);
}
