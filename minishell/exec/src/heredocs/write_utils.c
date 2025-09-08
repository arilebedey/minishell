#include "../../../include/command.h"
#include "../../../libft/libft.h"
#include "../../include/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	replace_heredoc_with_file(t_infile *in, char *filename)
{
	if (in->value)
		free(in->value);
	in->value = filename;
	in->heredoc_mode = 0;
	return (1);
}

static char	*generate_heredoc_filename(int index)
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
