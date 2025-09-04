#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

char	*generate_heredoc_filename(int index)
{
	char	*pid_str;
	char	*idx_str;
	char	*tmp;
	char	*filename;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	idx_str = ft_itoa(index);
	if (!idx_str)
		return (free(pid_str), NULL);
	tmp = ft_strjoin("/tmp/minishell_heredoc_", pid_str);
	free(pid_str);
	if (!tmp)
		return (free(idx_str), NULL);
	filename = ft_strjoin(tmp, idx_str);
	free(tmp);
	free(idx_str);
	return (filename);
}

// Write one heredoc into fd until delimiter is found
int	write_heredoc_to_fd(t_infile *infile, int fd)
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
	return (1);
}

int	open_temp_infile(char **filename, int index)
{
	int	fd;

	*filename = generate_heredoc_filename(index);
	if (!*filename)
		return (perror("heredoc filename"), -1);
	fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc tmpfile"), free(*filename), -1);
	return (fd);
}

int	write_heredocs_to_file(t_command *cmd, int fd)
{
	t_infile	*in;
	int			has_heredoc;

	in = cmd->head_infile;
	has_heredoc = 0;
	while (in)
	{
		if (in->heredoc_mode)
		{
			has_heredoc = 1;
			if (!write_heredoc_to_fd(in, fd))
				return (0);
		}
		in = in->next;
	}
	return (has_heredoc);
}
