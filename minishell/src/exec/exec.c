#include "../../includes/minishell.h"

static void	exec_cmd(t_ms *ms, t_tree *node)
{
	char	**paths;
	char	*cmd_path;
	char	**tmp_paths;
	char	*tmp;
	char	*full;

	if (!node->argv || !node->argv[0])
		exit_shell(ms, NULL, EXIT_FAILURE);
	paths = find_path(ms->env);
	if (!paths)
	{
		ft_putstr_fd("PATH not set\n", 2);
		exit_shell(ms, NULL, 127);
	}
	// If command contains '/', try directly
	if (strchr(node->argv[0], '/'))
		cmd_path = strdup(node->argv[0]);
	else
	{
		tmp_paths = paths;
		cmd_path = NULL;
		while (*tmp_paths)
		{
			tmp = ft_strjoin(*tmp_paths, "/");
			full = ft_strjoin(tmp, node->argv[0]);
			free(tmp);
			if (access(full, X_OK) == 0)
			{
				cmd_path = full;
				break ;
			}
			free(full);
			tmp_paths++;
		}
	}
	free_tab(paths);
	if (!cmd_path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(node->argv[0], 2);
		exit_shell(ms, NULL, 127);
	}
	execve(cmd_path, node->argv, ms->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	exec_redir_out(t_ms *ms, t_tree *root)
{
	int	fd;

	fd = open(root->right->tok->text, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("open");
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	close(fd);
	exec_ast(ms, root->left);
	exit_shell(ms, NULL, EXIT_FAILURE);
}

static void	exec_pipe(t_ms *ms, t_tree *root)
{
	int		fds[2];
	pid_t	left_child;
	pid_t	right_child;

	if (pipe(fds) < 0)
	{
		perror("pipe");
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	left_child = fork();
	if (left_child < 0)
	{
		perror("fork");
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	if (left_child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec_ast(ms, root->left);
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	right_child = fork();
	if (right_child < 0)
	{
		perror("fork");
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	if (right_child == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec_ast(ms, root->right);
		exit_shell(ms, NULL, EXIT_FAILURE);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(left_child, NULL, 0);
	waitpid(right_child, NULL, 0);
}

int	exec_ast(t_ms *ms, t_tree *root)
{
	if (!root || !root->tok)
		return (0);
	if (root->tok->type == T_WORD)
		exec_cmd(ms, root);
	else if (root->tok->type == T_REDIR_OUT)
		exec_redir_out(ms, root);
	else if (root->tok->type == T_PIPE)
		exec_pipe(ms, root);
	return (0);
}
