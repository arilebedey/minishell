#ifndef EXEC_H
# define EXEC_H

# include "../../include/command.h"
# include "../../include/env.h"

typedef struct s_child_ctx
{
	int	in_fd;
	int	need_pipe;
	int	pipefd[2];
}		t_child_ctx;

// Main exec function
int		exec(t_command *head_cmd, t_env *head_env);

// exec_pipeline.c
int		exec_pipeline(t_command *cmd, t_env *head_env);

// exec_command.c
void	exec_command(t_command *head_cmd, t_command *cmd, t_env *head_env);

// setup_redirs.c
void	setup_redirections(t_command *cmd);

// Convert env list to envp
char	**env_to_envp(t_env *head_env);
void	free_envp(char **envp);

// Convert args list
char	**args_to_argv(t_args *head_arg);
void	free_argv(char **argv);

#endif
