/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:52:44 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 12:52:44 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sig/sig.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

void	copy_signal_value(int signum)
{
	g_exit_status = 128 + signum;
}

void	readline_nl(int signum)
{
	copy_signal_value(signum);
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
