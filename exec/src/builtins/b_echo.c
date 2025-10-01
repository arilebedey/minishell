/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:03:42 by alebedev          #+#    #+#             */
/*   Updated: 2025/10/01 08:51:50 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/command.h"
#include "../../../include/env.h"
#include "../../../include/sig/sig.h"
#include "../../../libft/libft.h"

static int	is_n_flag(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 1;
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

int	builtin_echo(t_command *cmd, t_env *head_env)
{
	t_args	*arg;
	int		print_newline;

	(void)head_env;
	arg = cmd->head_arg;
	if (arg)
		arg = arg->next;
	print_newline = 1;
	while (arg && is_n_flag(arg->value))
	{
		print_newline = 0;
		arg = arg->next;
	}
	while (arg)
	{
		ft_printf("%s", arg->value);
		if (arg->next)
			ft_printf(" ");
		arg = arg->next;
	}
	if (print_newline)
		ft_printf("\n");
	g_exit_status = 0;
	return (0);
}
