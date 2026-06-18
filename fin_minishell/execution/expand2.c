/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:28:54 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:29:43 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	process_char_expansion(t_struct **cur, char *current_str, char **envp,
		int *i)
{
	int	result;

	if (current_str[*i] == '$' && current_str[*i + 1] == '?')
	{
		result = process_exit_status_at_position(cur, current_str, i);
		if (result != 0)
			return (result);
	}
	else if (current_str[*i] == '$' && current_str[*i + 1]
		&& (ft_isalpha(current_str[*i + 1]) || current_str[*i + 1] == '_'))
	{
		result = process_variable_at_position(cur, current_str, envp, i);
		if (result != 0)
			return (result);
	}
	else
		(*i)++;
	return (0);
}

int	expand_variable(t_struct **cur, char *str, char **envp)
{
	char	*current_str;
	int		i;
	int		result;

	current_str = str;
	i = 0;
	while (current_str[i])
	{
		result = process_char_expansion(cur, current_str, envp, &i);
		if (result != 0)
			return (result);
		current_str = (*cur)->str;
	}
	return (0);
}
