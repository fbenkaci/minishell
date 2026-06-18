/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:10:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/29 17:08:52 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_length_quotes(char *s, int *temp_i)
{
	char	quote_char;

	quote_char = s[*temp_i];
	(*temp_i)++;
	if (s[*temp_i] == quote_char)
	{
		(*temp_i)++;
		return (1);
	}
	else
		return (0);
}

int	calculate_word_length(char *s, int start)
{
	int	temp_i;
	int	content_len;

	temp_i = start;
	content_len = 0;
	while (s[temp_i] && s[temp_i] != ' ' && s[temp_i] != '<' && s[temp_i] != '>'
		&& s[temp_i] != '|' && s[temp_i] != '(' && s[temp_i] != ')')
	{
		if (s[temp_i] == '\"' || s[temp_i] == '\'')
		{
			if (!handle_length_quotes(s, &temp_i))
				break ;
		}
		else if (s[temp_i] == '=')
			break ;
		else
		{
			content_len++;
			temp_i++;
		}
	}
	return (content_len);
}

int	handle_extract_quotes(char *s, int *i)
{
	char	quote_char;

	quote_char = s[*i];
	(*i)++;
	if (s[*i] == quote_char)
	{
		(*i)++;
		return (1);
	}
	else
	{
		(*i)--;
		return (0);
	}
}

int	extract_word_content(char *s, int *i, char *word_content)
{
	int	j;

	j = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '|'
		&& s[*i] != '(' && s[*i] != ')')
	{
		if (s[*i] == '\"' || s[*i] == '\'')
		{
			if (!handle_extract_quotes(s, i))
				break ;
		}
		else if (s[*i] == '=')
			break ;
		else
		{
			word_content[j++] = s[*i];
			(*i)++;
		}
	}
	word_content[j] = '\0';
	return (j);
}

void	append_and_advance(t_struct **cur, t_struct *new)
{
	if (!new)
		return ;
	(*cur)->next = new;
	*cur = new;
}
