/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:05:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/29 17:05:46 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_quote_chars(char *str, char *clean)
{
	int	i;
	int	j;
	int	in_dquote;
	int	in_squote;

	i = 0;
	j = 0;
	in_dquote = 0;
	in_squote = 0;
	while (str[i])
	{
		if ((str[i] == '"' && !in_squote) || (str[i] == '\'' && !in_dquote))
		{
			if (str[i] == '"')
				in_dquote = !in_dquote;
			else
				in_squote = !in_squote;
			i++;
			continue ;
		}
		clean[j++] = str[i++];
	}
	return (j);
}

void	clean_quotes(t_struct *token)
{
	char	*clean;
	int		clean_len;
	size_t	original_len;

	if (!token || !token->str)
		return ;
	original_len = ft_strlen(token->str);
	clean = malloc(original_len + 1);
	if (!clean)
		return ;
	clean_len = process_quote_chars(token->str, clean);
	clean[clean_len] = '\0';
	if (clean_len != (int)original_len || ft_strcmp(token->str, clean) != 0)
	{
		free(token->str);
		token->str = clean;
	}
	else
		free(clean);
}
