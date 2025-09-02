#include "../../include/command.h"
#include "../../include/env.h"
#include "../../include/error.h"
#include "../../include/sig/sig.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char		**args_to_argv(t_args *head_arg);
void		free_argv(char **argv);
char		**env_to_envp(t_env *head_env);
void		free_envp(char **envp);

static void	setup_redirections(t_command *cmd)
{
	int			fd;
	t_infile	*in;
	t_outfile	*out;

	in = cmd->head_infile;
	while (in)
	{
		if (in->heredoc_mode == 0)
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
		}
		else
		{
			// TODO: heredoc handling
		}
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

static void	exec_command(t_command *cmd, t_env *head_env)
{
	char	**argv;
	char	**envp;

	if (!cmd->head_arg)
		exit(0);
	argv = args_to_argv(cmd->head_arg);
	if (!argv)
		exit(1);
	envp = env_to_envp(head_env);
	if (!envp)
		return (free_argv(argv), exit(1));
	setup_redirections(cmd);
	execve(argv[0], argv, envp);
	perror(argv[0]);
	free_argv(argv);
	free_envp(envp);
	exit(127);
}

static int	exec_pipeline(t_command *cmd, t_env *head_env)
{
	int		pipefd[2];
	pid_t	pid;
	int		in_fd;
	pid_t	last_pid;
	int		wstatus;

	in_fd = STDIN_FILENO;
	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) < 0)
			return (perror("pipe"), 0);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 0);
		if (pid == 0)
		{
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			exec_command(cmd, head_env);
		}
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
		last_pid = pid;
		cmd = cmd->next;
	}
	while ((pid = wait(&wstatus)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(wstatus))
				g_exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				g_exit_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (1);
}

int	exec(t_command *head_cmd, t_env *head_env)
{
	if (!head_cmd)
		return (1);
	if (!exec_pipeline(head_cmd, head_env))
		return (0);
	return (1);
}
