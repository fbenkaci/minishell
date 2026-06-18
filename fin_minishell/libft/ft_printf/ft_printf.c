/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:36:25 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/15 15:53:41 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char descriptor, va_list ap)
{
	int	count;

	count = 0;
	if (descriptor == 'c')
		count = ft_putchar((char)(va_arg(ap, int)));
	else if (descriptor == 's')
		count = ft_putstr((va_arg(ap, char *)));
	else if (descriptor == 'p')
		count = ft_modulo_p(va_arg(ap, unsigned long long), 16);
	else if (descriptor == 'd' || descriptor == 'i')
		count = ft_putnbr((va_arg(ap, int)));
	else if (descriptor == 'u')
		count = ft_unsigned_putnbr((va_arg(ap, int)));
	else if (descriptor == 'X')
		count = ft_putnbrbase_x_maj(va_arg(ap, int), 16);
	else if (descriptor == 'x')
		count = ft_putnbrbase_x(va_arg(ap, int), 16);
	if (descriptor == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (count);
}
