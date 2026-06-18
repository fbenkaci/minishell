/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:07:51 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/12/10 11:05:29 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_putnbr(unsigned int nb)
{
	long	nbr;
	int		count;

	nbr = nb;
	count = 0;
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar(nbr + 48);
		count++;
	}
	else
	{
		count += ft_unsigned_putnbr(nbr / 10);
		count += ft_unsigned_putnbr(nbr % 10);
	}
	return (count);
}
