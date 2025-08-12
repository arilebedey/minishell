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
	node->argv = NULL;
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

static char	**tokens_to_argv(t_token *tok)
{
	int		count;
	t_token	*tmp;
	char	**argv;
	t_token	*to_free;

	count = 0;
	tmp = tok;
	// Count consecutive T_WORD tokens
	while (tmp && tmp->type == T_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	// Fill argv and free extra tokens (keep the first one for node->tok)
	tmp = tok;
	count = 0;
	while (tmp && tmp->type == T_WORD)
	{
		argv[count++] = strdup(tmp->text);
		if (tmp != tok) // free all except the first token
		{
			to_free = tmp;
			tmp = tmp->next;
			free(to_free->text);
			free(to_free);
			continue ;
		}
		tmp = tmp->next;
	}
	argv[count] = NULL;
	// Detach the first token from the rest
	tok->next = tmp;
	return (argv);
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
	n = new_node(tok);
	if (!n)
		return (NULL);
	n->argv = tokens_to_argv(tok);
	return (n);
}
