#include "../../include/command.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	setup_redirections(t_command *cmd)
{
	int			fd;
	t_infile	*in;
	t_outfile	*out;

	in = cmd->head_infile;
	while (in)
	{
		fd = open(in->value, O_RDONLY);
		if (fd < 0)
		{
			perror(in->value);
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2 infile");
			exit(1);
		}
		close(fd);
		in = in->next;
	}
	out = cmd->head_outfile;
	while (out)
	{
		if (out->append_mode)
			fd = open(out->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(out->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(out->value);
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");
			exit(1);
		}
		close(fd);
		out = out->next;
	}
}
