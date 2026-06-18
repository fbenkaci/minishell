/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:10:48 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/12/10 11:05:21 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	long int	nbr;
	int			count;

	count = 0;
	nbr = nb;
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar('-');
		count++;
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar(nbr + 48);
		count++;
	}
	else
	{
		count += ft_putnbr(nbr / 10);
		count += ft_putnbr(nbr % 10);
	}
	return (count);
}
