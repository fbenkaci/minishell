/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modulo_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:53:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/02/03 17:07:28 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_modulo_p(unsigned long long nb, unsigned int base)
{
	int		count;
	char	*base_16;

	count = 0;
	base_16 = "0123456789abcdef";
	if (!nb)
		return (write(1, "(nil)", 5));
	if (nb < base)
		count += ft_putstr("0x");
	if (nb >= base)
	{
		count += ft_modulo_p((nb / base), base);
	}
	count += ft_putchar(base_16[nb % base]);
	return (count);
}
