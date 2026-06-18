/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/18 15:47:35 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	size_src;

	size_src = ft_strlen((char *)src);
	i = 0;
	if (dest_size == 0)
		return (size_src);
	while (src[i] && i < dest_size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (size_src);
}

// int	main(void)
// {
// 	char dest[5];
// 	char src[12] = "abcdefghjdd";

// 	printf("%ld\n", strlcpy(dest, src, sizeof(dest)));
// 	//printf("%s", dest);
// 	return (0);
// }