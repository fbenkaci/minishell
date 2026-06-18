/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:33:27 by fbenkaci          #+#    #+#             */
/*   Updated: 2024/11/26 11:09:02 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		size_s1_s2;

	size_s1_s2 = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(size_s1_s2 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, size_s1_s2);
	ft_strlcat(dest, s2, size_s1_s2);
	return (dest);
}
