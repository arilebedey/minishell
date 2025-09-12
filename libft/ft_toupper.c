/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:13:28 by agense            #+#    #+#             */
/*   Updated: 2025/05/01 20:13:33 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If c is a lowercase letter, returns its uppercase equivalent.
// Otherwise, returns c.
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
