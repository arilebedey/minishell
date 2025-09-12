/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:40:22 by agense            #+#    #+#             */
/*   Updated: 2025/05/21 12:31:18 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Write a number in the base given
// Returns the number of digits (for the pointer case essentially)
int	ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int	base_len;
	int				modulo_result;
	int				count;

	count = 1;
	base_len = ft_strlen(base);
	modulo_result = nbr % base_len;
	if (nbr >= base_len)
	{
		nbr = nbr / base_len;
		count += ft_putnbr_base(nbr, base);
	}
	return (ft_putchar_fd(base[modulo_result], 1), count);
}

int	ft_putnbr_base_address(unsigned long long nbr, char *base)
{
	unsigned int	base_len;
	int				modulo_result;
	int				count;

	count = 1;
	base_len = ft_strlen(base);
	modulo_result = nbr % base_len;
	if (nbr >= base_len)
	{
		nbr = nbr / base_len;
		count += ft_putnbr_base_address(nbr, base);
	}
	return (ft_putchar_fd(base[modulo_result], 1), count);
}

// Write the unsigned number n in the file descriptor fd.
void	ft_putunsignednbr_fd(unsigned int n, int fd)
{
	int	c;

	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	ft_putstr_fd((char *)&c, fd);
}
