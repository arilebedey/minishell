#include "../../includes/minishell.h"

void	free_tokens(t_token *tok)
{
	t_token	*nx;

	while (tok)
	{
		nx = tok->next;
		free(tok->text);
		free(tok);
		tok = nx;
	}
}

void	cleanup_ms(t_ms *ms, t_token *tokens)
{
	if (tokens)
		free_tokens(tokens);
	if (ms->ast)
	{
		free_ast(ms->ast);
		ms->ast = NULL;
	}
}

void	exit_shell(t_ms *ms, t_token *tokens, int status)
{
	cleanup_ms(ms, tokens);
	rl_clear_history();
	exit(status);
}

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->tok)
	{
		free(node->tok->text);
		free(node->tok);
	}
	free_tab(node->argv);
	free(node);
}
