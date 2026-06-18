/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:21:49 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/21 16:46:22 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_quote(t_struct *data)
{
	int	i;
	int	inside_squote;
	int	inside_dquote;

	inside_squote = 0;
	inside_dquote = 0;
	i = -1;
	while (++i, data->str[i])
	{
		if (data->str[i] == '\'' && !inside_dquote)
			inside_squote = !inside_squote;
		else if (data->str[i] == '\"' && !inside_squote)
			inside_dquote = !inside_dquote;
	}
	if (inside_squote)
	{
		printf("Syntax error: unclosed single quote\n");
		return (0);
	}
	if (inside_dquote)
	{
		printf("Syntax error: unclosed double quote\n");
		return (0);
	}
	return (1);
}
