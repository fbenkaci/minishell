/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:10:30 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/26 11:09:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*destt;
	unsigned const char	*srcc;

	destt = (unsigned char *)dest;
	srcc = (unsigned const char *)src;
	if (destt == src)
		return (destt);
	if (destt < srcc)
		return (ft_memcpy(destt, srcc, n));
	else
	{
		i = n;
		while (i > 0)
		{
			--i;
			destt[i] = srcc[i];
		}
	}
	return (dest);
}
