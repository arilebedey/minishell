/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:40:19 by agense            #+#    #+#             */
/*   Updated: 2025/08/26 21:54:18 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>

// Prints the number n and returns the number of characters printed (\0 exclude)
int	printf_number_base10(int n)
{
	if (n >= 0)
		return (ft_putnbr_fd(n, 1), count_digit(n));
	return (ft_putnbr_fd(n, 1), count_digit(n) + 1);
}

int	printf_unsigned_number_base10(unsigned int n)
{
	return (ft_putunsignednbr_fd(n, 1), count_digit_unsigned(n));
}

int	printf_number_base16_lowercase(unsigned int n)
{
	return (ft_putnbr_base(n, "0123456789abcdef"));
}

int	printf_address(void *p)
{
	unsigned long long	c;

	if (!p)
		return (ft_putstr_fd("(nil)", 1), 5);
	ft_putstr_fd("0x", 1);
	c = (unsigned long long)p;
	return (ft_putnbr_base_address(c, "0123456789abcdef") + 2);
}

int	printf_number_base16_uppercase(unsigned int n)
{
	return (ft_putnbr_base(n, "0123456789ABCDEF"));
}
