/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:23:34 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/26 11:10:24 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*strr;
	size_t			i;

	strr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		strr[i] = 0;
		i++;
	}
}
