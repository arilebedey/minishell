/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:03:13 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:03:27 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parse/include/token.h"
#include "../../include/debug.h"
#include "../../libft/libft.h"

// Prints value and type of all token elements.
void	debug_token_list(t_token *head_tk)
{
	(void)head_tk;
}

	//t_token	*curr_tk;

	//if (!DEBUG_TOKEN)
	//	return ;
	//curr_tk = head_tk;
	//while (curr_tk)
	//{
	//	ft_printf("\nType: ");
	//	if (curr_tk->type == T_WORD)
	//		ft_printf("T_WORD");
	//	else if (curr_tk->type == T_PIPE)
	//		ft_printf("T_PIPE");
	//	else if (curr_tk->type == T_IN)
	//		ft_printf("T_IN");
	//	else if (curr_tk->type == T_OUT)
	//		ft_printf("T_OUT");
	//	else if (curr_tk->type == T_APPEND)
	//		ft_printf("T_APPEND");
	//	else if (curr_tk->type == T_HEREDOC)
	//		ft_printf("T_HEREDOC");
	//	else
	//		ft_printf("error: debug_token_list");
	//	ft_printf("\nValue: %s", curr_tk->value);
	//	curr_tk = curr_tk->next;
	//}
	//ft_printf("\n\n");