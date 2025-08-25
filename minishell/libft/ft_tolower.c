/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:16:49 by agense            #+#    #+#             */
/*   Updated: 2025/05/01 20:16:52 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If c is a lowercase letter, returns its uppercase equivalent.
// Otherwise, returns c.
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
