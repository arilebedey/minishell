/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:40:15 by agense            #+#    #+#             */
/*   Updated: 2025/06/24 18:37:48 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include "../libft.h"

int		printf_unsigned_number_base10(unsigned int n);
void	ft_putunsignednbr_fd(unsigned int n, int fd);
int		print_accor_to_type(char c, va_list *p_args);
int		printf_number_base16_uppercase(unsigned int n);
int		printf_number_base16_lowercase(unsigned int n);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_putnbr_base_address(unsigned long long nbr, char *base);
int		count_digit_unsigned(unsigned int n);
int		printf_string(const char *s);
int		printf_number_base10(int n);
int		count_digit_base16(int n);
int		printf_address(void *p);
int		count_digit(int n);
#endif