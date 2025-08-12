#include "../includes/minishell.h"

static t_node	*new_node(t_token *tok)
{
	t_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->tok = tok;
	return (node);
}

/* find the rightmost separator of given type */
static t_token	*find_sep(t_token *tok, t_token_type type)
{
	t_token	*cur;
	t_token	*last;

	cur = tok;
	last = NULL;
	while (cur)
	{
		if (cur->type == type)
			last = cur;
		cur = cur->next;
	}
	return (last);
}

static t_node	*build(t_token *tok, t_token_type sep)
{
	t_token	*s;
	t_token	*right;
	t_node	*n;

	s = find_sep(tok, sep);
	if (!s || s == tok || s->next == NULL)
		return (NULL);
	right = s->next;
	s->next = NULL;
	n = new_node(s);
	if (!n)
		return (NULL);
	n->left = build_ast(tok);
	n->right = build_ast(right);
	return (n);
}

t_node	*build_ast(t_token *tok)
{
	t_node	*n;

	if (!tok)
		return (NULL);
	n = build(tok, T_REDIR_OUT);
	if (n)
		return (n);
	n = build(tok, T_PIPE);
	if (n)
		return (n);
	return (new_node(tok));
}
