#include "../include/token.h"
#include <malloc.h>

void	free_token_list(t_token *head_tk)
{
	if (head_tk->next)
	{
		free(head_tk->value);
		free_token_list(head_tk->next);
	}
	free(head_tk);
	head_tk = NULL;
}
