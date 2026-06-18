/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:20:46 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/12/10 11:05:57 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrbase_x(unsigned int nb, unsigned int base)
{
	int		count;
	char	*base_16;

	count = 0;
	base_16 = "0123456789abcdef";
	if (nb < base)
	{
		count += ft_putchar(base_16[nb]);
		return (count);
	}
	else
	{
		count += ft_putnbrbase_x((nb / base), base);
		count += ft_putnbrbase_x((nb % base), base);
	}
	return (count);
}
