#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

# include "minishell_structs.h"

/* ROOT FOLDER */
// main.c
// ast.c
t_node	*build_ast(t_token *tok);
void	free_ast(t_node *root);
// process_line.c
void	process_line(t_ms *ms, char *line);

/* EXEC */
// cmd.c
char	**find_path(char **env);
char	**get_cmd(char **paths, char *cmd);
// exec.c
int		exec_ast(t_ms *ms, t_node *root);

/* FREE */
// free_tab.c
void	free_tab(char **tab);
// cleanup.c
void	cleanup_ms(t_ms *ms, t_token *tokens);
void	exit_shell(t_ms *ms, t_token *tokens, int status);
void	free_ast(t_node *r);
void	free_tokens(t_token *tok);

/* LEXER */
// lexer.c
t_token	*lexer(const char *line);
// syntax.c
int		syntax_error(t_token *tok);
#endif
