#ifndef EXEC_H
# define EXEC_H

// Main exec function
int		exec(t_command *head_cmd, t_env *head_env);

// Convert env list to envp
char	**env_to_envp(t_env *head_env);
void	free_envp(char **envp);

// Convert args list
char	**args_to_argv(t_args *head_arg);
void	free_argv(char **argv);

#endif
