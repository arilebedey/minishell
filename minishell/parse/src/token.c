#include "../include/token.h"
#include <malloc.h>

t_token	*init_tk_element(void)
{
	t_token *curr_tk;

	curr_tk = malloc(sizeof(t_token));
	if (!curr_tk)
		return (perror("init_tk_element"), NULL);
	curr_tk->type = T_WORD;
	curr_tk->value = NULL;
	curr_tk->next = NULL;
	return (curr_tk);
}

void	free_token_list(t_token **ref_head_tk)
{
	if (!*ref_head_tk)
		return ;
	if ((*ref_head_tk)->next)
		free_token_list(&(*ref_head_tk)->next);
	free((*ref_head_tk)->value);
	free(*ref_head_tk);
	*ref_head_tk = NULL;
}

