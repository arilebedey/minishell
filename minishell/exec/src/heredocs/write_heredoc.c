#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern t_env	*g_head_env;
static t_infile	*g_current_infile = NULL;

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

static void	heredoc_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	free_env_list(g_head_env);
	if (g_current_infile && g_current_infile->value)
		free(g_current_infile->value);
	exit(130);
}

static void	child_write_heredoc(t_infile *infile, int fd, char *tmpname)
{
	char	*line;

	g_current_infile = infile;
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
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
	close(fd);
	free(tmpname);
	free(infile->value);
	free_env_list(g_head_env);
	exit(0);
}

int	write_heredoc_to_fd(t_infile *infile, int fd, char *tmpname)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork heredoc"), 0);
	if (pid == 0)
		child_write_heredoc(infile, fd, tmpname);
	if (!init_parent_sigaction())
		return (0);
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid heredoc"), 0);
	if (!init_interactive_sigaction())
		return (0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	return (1);
}

int	write_heredocs_to_file(t_command *cmd, int fd, char *filename)
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
			if (!write_heredoc_to_fd(in, fd, filename))
				return (0);
		}
		in = in->next;
	}
	return (has_heredoc);
}
