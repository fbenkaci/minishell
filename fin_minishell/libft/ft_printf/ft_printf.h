/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:57:00 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/12/08 10:08:49 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_putchar(int c);
int	ft_putnbr(int nbr);
int	ft_putstr(const char *str);
int	ft_unsigned_putnbr(unsigned int nb);
int	ft_putnbrbase_x_maj(unsigned int nb, unsigned int base);
int	ft_putnbrbase_x(unsigned int nb, unsigned int base);
int	ft_modulo_p(unsigned long long nb, unsigned int base);
int	ft_printf(const char *format, ...);

#endif