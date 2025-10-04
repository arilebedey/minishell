/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:36 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/04 08:59:04 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/command.h"
# include "../../include/env.h"

int		try_exec_builtin(t_command *cmd, t_env *head_env, int is_parent);

// b_exit.c
int		builtin_exit(t_command *cmd, t_env *head_env, int is_parent);

// b_cd.c
int		builtin_cd(t_command *cmd, t_env *head_env);

// b_cd_utils.c
int		update_env_var(t_env *head_env, const char *key, const char *value);
int		update_pwd_and_oldpwd(t_env *head_env, const char *oldpwd);
int		update_env_vars(t_env *head_env, char *oldpwd);

// b_env.c
int		builtin_env(t_command *cmd, t_env *head_env);

// b_echo.c
int		builtin_echo(t_command *cmd, t_env *head_env);

// b_export.c
int		builtin_export(t_command *cmd, t_env *head_env);

// b_export_setvar.c
int		set_variable(t_env *head_env, const char *arg);

// b_export_utils.c
t_env	*find_env(t_env *head_env, const char *key);
int		is_valid_identifier(const char *s);
void	print_identifier_error(const char *arg);
void	print_env_export(t_env *head_env);
int		append_new_env(t_env **head_env, char *key, char *value);

// b_pwd.c
int		builtin_pwd(void);

// b_unset.c
int		builtin_unset(t_command *cmd, t_env **head_env);

// helpers.c
int		is_numeric(const char *s);
long	simple_atol(const char *s);
int		append_new_env(t_env **head_env, char *key, char *value);

// helpers2.c
int		setup_parent_redirections(t_command *cmd, int *saved_fds);
void	restore_fds(int *saved_fds);

#endif
