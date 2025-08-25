/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:23:29 by agense            #+#    #+#             */
/*   Updated: 2025/08/25 15:22:56 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// Checks whether c is a 7-bit unsigned char value that fits into the ASCII
// character set
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
