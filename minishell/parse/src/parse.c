#include "../../include/command.h"
#include "../../include/env.h"
#include "../../libft/libft.h"
#include "../include/parse.h"
#include "../include/token.h"

t_command	*parse(const char* line, t_env *head_env)
{
	(void)head_env;
	t_token		*head_tk;
	t_command	*head_cmd;

	head_tk = lexer(line);
	if (!head_tk)
		return (NULL);
	// TODO: check_syntax
	head_cmd = build_command_list(head_tk);
	if (!head_cmd)
		return (free_token_list(head_tk), NULL);
	// TODO: expansion
	free_token_list(head_tk);
	return (head_cmd);
}
