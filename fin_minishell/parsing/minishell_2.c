/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:21:07 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/06 17:01:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_chain(t_struct *tokens)
{
	t_struct	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->str)
		{
			free(tokens->str);
			tokens->str = NULL;
		}
		free(tokens);
		tokens = tmp;
	}
}

void	free_tokens(t_struct *data)
{
	t_struct	*tmp;

	while (data)
	{
		if (data->env)
			ft_free_array(data->env);
		tmp = data->next;
		if (data->str)
			free(data->str);
		free(data);
		data = tmp;
	}
}

int	is_str_only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'
			&& str[i] != '\v' && str[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}
