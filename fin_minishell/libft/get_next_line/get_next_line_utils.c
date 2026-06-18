/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:54:10 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/15 15:54:12 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len_s;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	dest = malloc(len_s * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	int		len_s1_s2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len_s1_s2 = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((len_s1_s2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*sub_s;
// 	size_t	i;
// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;

// 	sub_s = malloc((len + 1) * sizeof(char));
// 	if (!sub_s)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		sub_s[i] = s[start + i];
// 		i++;
// 	}
// 	sub_s[i] = '\0';
// 	return (sub_s);
// }

// int	main(void)
// {
// 	char *str;
// 	char s1[] = "Bonjour";
// 	// char s2[] = "WORLD";
// 	str = ft_substr(s1, 2, 10);

// 	printf("%s", str);
// 	return (0);
// }