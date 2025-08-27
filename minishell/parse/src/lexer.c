#include "../../include/env.h"
#include "../include/token.h"
#include "../../libft/libft.h"
#include <malloc.h>

// Returns a new token linked list.
// If failed, prints error msg and returns a NULL pointer.
static t_token	*init_tk_list(void);

t_token	*lexer(const char *line)
{
	//int		i;
	//int		j;
	(void)line;
	t_token *head_tk;
	t_token	*curr_tk;

	head_tk = init_tk_list();
	if (!head_tk)
		return (NULL);
	curr_tk = head_tk;
	//i = -1;
	//while (line[++i])
	//{
	//	if (line[i] == 'A')
	//		continue ;
	//	j = i - 1;
	//	while (line[++j] != 'A')
	//		;
	//	curr_tk->type = T_WORD;
	//	curr_tk->value = ft_substr(line, i, j - i);
	//	if (!curr_tk->value)
	//		return (perror("lexer substr"), NULL);
	//	if (line[i + 1])
	//	{
	//		curr_tk->next = malloc(sizeof(t_token));
	//		if (!curr_tk->next)
	//			return (perror("lexer malloc"),NULL);
	//	}
	//}
	return (head_tk);
}

static t_token	*init_tk_list(void)
{
	t_token *head_tk;

	head_tk = malloc(sizeof(t_token));
	if (!head_tk)
		return (perror("head_tk malloc"), NULL);
	head_tk->type = T_WORD;
	head_tk->value = NULL;
	head_tk->next = NULL;
	return (head_tk);
}
