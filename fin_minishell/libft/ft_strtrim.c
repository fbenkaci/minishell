/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:08:00 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/26 11:08:05 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		size_s1;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	size_s1 = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[size_s1 - 1]) && size_s1)
		size_s1--;
	if (size_s1 - i < 0)
		dest = malloc(1);
	else
	{
		dest = malloc((size_s1 - i) * sizeof(char) + 1);
		if (!dest)
			return (NULL);
	}
	ft_strlcpy(dest, s1 + i, size_s1 + 1 - i);
	return (dest);
}
