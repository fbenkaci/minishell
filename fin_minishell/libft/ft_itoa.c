/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:14:01 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/26 11:10:13 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_size(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb < 0)
		i++;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static char	*copie(unsigned long int tmp, int i, char *dest)
{
	while (tmp != 0)
	{
		dest[i - 1] = (tmp % 10) + 48;
		tmp = tmp / 10;
		i--;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*dest;
	long int	tmp;

	tmp = (long int)n;
	i = number_size(n);
	dest = malloc((i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (tmp < 0)
	{
		*dest = '-';
		tmp *= -1;
	}
	if (tmp == 0)
		dest[0] = '0';
	dest[i] = '\0';
	if (tmp != 0)
	{
		copie(tmp, i, dest);
	}
	return (dest);
}
