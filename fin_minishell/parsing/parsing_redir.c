/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:40 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/29 17:18:03 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir(t_struct *data, int i, int *found_redir)
{
	if (data->str[i] == '>')
		return (handle_output_redir(data, i, found_redir));
	else if (data->str[i] == '<')
		return (handle_input_redir(data, i, found_redir));
	return (i);
}

int	utils_parse_redir(t_struct *data, int i, int *found_redir)
{
	while (data->str[i])
	{
		i = process_char(data, i, found_redir);
		if (i == -1)
			return (-1);
	}
	if (*found_redir)
		return (-1);
	return (i);
}

char	*process_redir_char(t_struct *data, int i)
{
	i++;
	if (data->str[i] && (data->str[i] == '<' || data->str[i] == '>'))
		i++;
	while (data->str[i] && data->str[i] == ' ')
		i++;
	if (!data->str[i])
		return ("newline");
	else if (data->str[i] == '|')
		return ("|");
	else if (data->str[i] == '>' && data->str[i + 1] == '>')
		return (">>");
	else if (data->str[i] == '>')
		return (">");
	else if (data->str[i] == '<' && data->str[i + 1] == '<')
		return ("<<");
	else if (data->str[i] == '<')
		return ("<");
	return (NULL);
}

char	*get_error_token(t_struct *data)
{
	int		i;
	char	*result;

	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == '<' || data->str[i] == '>')
		{
			result = process_redir_char(data, i);
			if (result)
				return (result);
		}
		else if (data->str[i] == '>' && data->str[i + 1] == '>'
			&& data->str[i + 2] == '>')
			return (">");
		i++;
	}
	return ("newline");
}

int	parse_redir(t_struct *data)
{
	int		i;
	int		found_redir;
	char	*error_token;

	i = 0;
	found_redir = 0;
	while (data->str[i] && data->str[i] == ' ')
		i++;
	i = utils_parse_redir(data, i, &found_redir);
	if (i == -1)
	{
		error_token = get_error_token(data);
		ft_putstr_fd(" syntax error near unexpected token `", 2);
		ft_putstr_fd(error_token, 2);
		ft_putstr_fd("'\n", 2);
		data->exec->last_status = 2;
		return (0);
	}
	return (1);
}
