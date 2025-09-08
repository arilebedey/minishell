#include "../../../include/command.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	heredoc_sigint(int signum)
{
	(void)signum;
	g_exit_status = 130;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

int	write_heredoc_to_fd(t_infile *infile, int fd, char *tmpname,
		t_command *head_cmd)
{
	struct sigaction	orig_int;
	struct sigaction	act_int;
	int					save_stdin;
	char				*line;

	(void)tmpname;
	(void)head_cmd;
	g_exit_status = 0;
	save_stdin = dup(STDIN_FILENO);
	if (save_stdin < 0)
		return (perror("dup stdin"), 0);
	sigaction(SIGINT, NULL, &orig_int);
	act_int = orig_int;
	act_int.sa_handler = heredoc_sigint;
	act_int.sa_flags |= SA_RESTART;
	sigemptyset(&act_int.sa_mask);
	if (sigaction(SIGINT, &act_int, NULL) == -1)
		return (perror("sigaction heredoc"), close(save_stdin), 0);
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
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	sigaction(SIGINT, &orig_int, NULL);
	if (g_exit_status == 130)
		return (0);
	return (1);
}

int	write_heredocs_to_file(t_command *cmd, int fd, char *filename)
{
	t_infile	*in;
	int			has_heredoc;

	(void)filename;
	in = cmd->head_infile;
	has_heredoc = 0;
	while (in)
	{
		if (in->heredoc_mode)
		{
			has_heredoc = 1;
			if (!write_heredoc_to_fd(in, fd, filename, cmd))
				return (0);
		}
		in = in->next;
	}
	return (has_heredoc);
}
