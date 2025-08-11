/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:11:42 by alebedev          #+#    #+#             */
/*   Updated: 2025/08/11 20:40:36 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

# include "minishell_structs.h"

/* ROOT FOLDER */
// main.c
// ast.c
t_tree	*build_ast(t_token *tok);
void	free_ast(t_tree *root);
// process_line.c
void	process_line(t_ms *ms, char *line);

/* EXEC */
// cmd.c
char	**find_path(char **env);
char	**get_cmd(char **paths, char *cmd);
// exec.c
int		exec_ast(t_ms *ms, t_tree *root);

/* FREE */
// free_tab.c
void	free_tab(char **tab);
// cleanup.c
void	cleanup_ms(t_ms *ms, t_token *tokens);
void	exit_shell(t_ms *ms, t_token *tokens, int status);
void	free_ast(t_tree *r);
void	free_tokens(t_token *tok);

/* LEXER */
// lexer.c
t_token	*lexer(const char *line);
// syntax.c
int		syntax_error(t_token *tok);
#endif
