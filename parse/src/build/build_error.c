/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:10:08 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:10:09 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/error.h"

// Prints a error msg according to c (\n or |).
static void	print_parse_error(const char c);

int	parse_exit(const char c, t_command *head_cmd)
{
	print_parse_error(c);
	free_cmd_list(&head_cmd);
	return (0);
}

static void	print_parse_error(const char c)
{
	if (c == '|')
		print_error("parse error near `|'\n");
	else if (c == '\n')
		print_error("parse error near `\\n'\n");
	else
		print_error("WHAT THE FUCK");
}
