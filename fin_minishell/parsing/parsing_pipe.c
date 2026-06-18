/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:48:22 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/29 16:44:34 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_quotes(t_struct *data, int i, int *found_pipe)
{
	char	quote;

	quote = data->str[i];
	i++;
	while (data->str[i] && data->str[i] != quote)
		i++;
	if (data->str[i])
		i++;
	*found_pipe = 0;
	return (i);
}

int	utils_parse_pipe(t_struct *data, int i, int *found_pipe)
{
	while (data->str[i])
	{
		if (data->str[i] == '\'' || data->str[i] == '"')
			i = handle_pipe_quotes(data, i, found_pipe);
		else if (data->str[i] == '|')
		{
			if (*found_pipe)
			{
				*found_pipe = 2;
				return (0);
			}
			*found_pipe = 1;
			i++;
		}
		else if (data->str[i] == ' ')
			i++;
		else
		{
			*found_pipe = 0;
			while (data->str[i] && data->str[i] != ' ' && data->str[i] != '|'
				&& data->str[i] != '\'' && data->str[i] != '"')
				i++;
		}
	}
	return (i);
}

int	parse_error_pipe(t_struct *data)
{
	int	i;
	int	found_pipe;

	i = 0;
	found_pipe = 0;
	while (data->str[i] && data->str[i] == ' ')
		i++;
	if (data->str[i] == '|')
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		data->exec->last_status = 2;
		return (0);
	}
	i = utils_parse_pipe(data, i, &found_pipe);
	if (found_pipe > 0)
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		data->exec->last_status = 2;
		return (0);
	}
	return (1);
}
