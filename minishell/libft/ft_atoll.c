/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:35:18 by agense            #+#    #+#             */
/*   Updated: 2025/06/16 18:35:26 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks whether c is a white-space character
static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// Converts the initial portion of the string pointed to by s to long long.
long long	ft_atoll(const char *s)
{
	long long	result;
	int			result_sign;
	int			i;

	result = 0;
	result_sign = 1;
	i = -1;
	while (ft_isspace(s[++i]))
		;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			result_sign = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + s[i++] - 48;
	return (result * result_sign);
}
