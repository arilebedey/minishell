/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:14:40 by agense            #+#    #+#             */
/*   Updated: 2025/05/18 15:04:54 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

// Returns the number of digits in n
static int	nbr_digit(int n)
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

// Returns absolute value of n
static int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// Reverse string s.
// Returns s reversed.
static char	*reverse(char *s)
{
	int		len;
	int		i;
	char	temp;

	i = -1;
	len = ft_strlen(s);
	while (++i < --len)
	{
		temp = s[i];
		s[i] = s[len];
		s[len] = temp;
	}
	return (s);
}

// Converts n to string.
char	*ft_itoa(int n)
{
	char	*result;
	int		is_negative;
	int		i;
	int		n_digit;

	n_digit = nbr_digit(n);
	is_negative = 0;
	i = -1;
	if (n < 0)
		is_negative = 1;
	result = malloc(sizeof(char) * (n_digit + is_negative + 1));
	if (!result)
		return (NULL);
	while (++i < n_digit)
	{
		result[i] = abs_value(n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		result[i++] = '-';
	result[i] = 0;
	result = reverse(result);
	return (result);
}
