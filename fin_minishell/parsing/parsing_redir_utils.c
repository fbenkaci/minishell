/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:05:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/29 16:42:42 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redir(t_struct *data, int i, int *found_redir)
{
	if (*found_redir && (i == 0 || data->str[i - 1] != '<'))
		return (-1);
	if (data->str[i + 1] && data->str[i + 1] == '>')
	{
		i++;
		if (data->str[i + 1] && data->str[i + 1] == '>')
			return (-1);
	}
	*found_redir = 1;
	return (i + 1);
}

int	handle_input_redir(t_struct *data, int i, int *found_redir)
{
	if (*found_redir && (!data->str[i + 1] || data->str[i + 1] != '>'))
		return (-1);
	if (data->str[i + 1] && data->str[i + 1] == '|')
		return (-1);
	if (data->str[i + 1])
	{
		if (data->str[i + 1] == '<' || data->str[i + 1] == '>')
			i++;
	}
	*found_redir = 1;
	return (i + 1);
}

int	handle_token_chars(t_struct *data, int i, int *found_redir)
{
	*found_redir = 0;
	while (data->str[i] && data->str[i] != ' ' && data->str[i] != '>'
		&& data->str[i] != '<' && data->str[i] != '|' && data->str[i] != '\''
		&& data->str[i] != '"')
		i++;
	return (i);
}

int	handle_quote_chars(t_struct *data, int i, int *found_redir)
{
	char	quote;

	quote = data->str[i];
	i++;
	while (data->str[i] && data->str[i] != quote)
		i++;
	if (data->str[i])
		i++;
	*found_redir = 0;
	return (i);
}

int	process_char(t_struct *data, int i, int *found_redir)
{
	if (data->str[i] == '\'' || data->str[i] == '"')
		i = handle_quote_chars(data, i, found_redir);
	else if (data->str[i] == '>' || data->str[i] == '<')
	{
		i = handle_redir(data, i, found_redir);
		if (i == -1)
			return (-1);
	}
	else if (data->str[i] == '|')
	{
		if (*found_redir)
			return (-1);
		i++;
	}
	else if (data->str[i] == ' ')
		i++;
	else
		i = handle_token_chars(data, i, found_redir);
	return (i);
}
