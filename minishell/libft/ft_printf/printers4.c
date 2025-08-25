/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:40:26 by agense            #+#    #+#             */
/*   Updated: 2025/06/10 14:53:58 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// Returns the number of digits in n
int	count_digit(int n)
{
	int	pot;
	int	nbr_digit;

	if (n == 0)
		return (1);
	nbr_digit = 10;
	pot = 1000000000;
	while (!(n / pot))
	{
		nbr_digit--;
		pot /= 10;
	}
	return (nbr_digit);
}

// Returns the number of digits in n (unsigned)
int	count_digit_unsigned(unsigned int n)
{
	int	pot;
	int	nbr_digit;

	if (n == 0)
		return (1);
	nbr_digit = 10;
	pot = 1000000000;
	while (!(n / pot))
	{
		nbr_digit--;
		pot /= 10;
	}
	return (nbr_digit);
}

int	count_digit_base16(int n)
{
	int	count;

	count = 1;
	while (n > 15)
	{
		n /= 16;
		count++;
	}
	return (count);
}
