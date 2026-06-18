/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:00:11 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/26 11:09:39 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*strr;
	size_t			i;

	strr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		strr[i] = (unsigned char)c;
		i++;
	}
	return (strr);
}
