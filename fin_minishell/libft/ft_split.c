/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:43:15 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/05/09 17:40:48 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*extract_word(char const *s, char c, int *len)
{
	char	*dest;
	int		start;
	int		i;

	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	while (s[start + i] && s[start + i] != c)
		i++;
	*len = i;
	dest = malloc((i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < *len)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

static char	**free_word(char **word, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(word[i]);
		i++;
	}
	free(word);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		len;
	int		i;

	i = 0;
	dest = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!s || !(dest))
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			dest[i] = extract_word(s, c, &len);
			if (!dest[i])
				return (free_word(dest, i));
			i++;
			s += len;
		}
		else
			s++;
	}
	dest[i] = NULL;
	return (dest);
}

// void free_split(char **split)
// {
// 	int i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }
// int main(void)
// {
// 	char **dest = NULL;
// 	int i;
// 	char s[] = "hello world";
// 	dest = ft_split(s, '\n');
// 	i = 0;
// 	while (dest[i] != NULL) {
// 	printf("%s\n", dest[i]);
// 	i++;
//     }
// 	free_split(dest);

// 	return (0);
// }
