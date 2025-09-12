/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:40:26 by agense            #+#    #+#             */
/*   Updated: 2025/06/10 14:53:58 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

// Prints the string s and returns the number of characters printed (\0 exclude)
int	printf_string(const char *s)
{
	int	i;

	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	i = -1;
	while (s[++i])
		ft_putchar_fd(s[i], 1);
	return (i);
}

// Check the type given in c and print via functions according to the type
int	print_accor_to_type(char c, va_list *p_args)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(*p_args, int), 1);
		return (1);
	}
	if (c == 's')
		return (printf_string(va_arg(*p_args, char *)));
	if (c == 'd' || c == 'i')
		return (printf_number_base10(va_arg(*p_args, int)));
	if (c == 'u')
		return (printf_unsigned_number_base10(va_arg(*p_args, unsigned int)));
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	if (c == 'x')
		return (printf_number_base16_lowercase(va_arg(*p_args, unsigned int)));
	if (c == 'X')
		return (printf_number_base16_uppercase(va_arg(*p_args, unsigned int)));
	if (c == 'p')
		return (printf_address(va_arg(*p_args, void *)));
	return (0);
}
