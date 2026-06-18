/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:20:44 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 17:21:14 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_join_tokens(t_struct *current, t_struct *next)
{
	if (!current || !next)
		return (0);
	if (next->type == SPACES)
		return (0);
	if (current->str && ft_strcmp(current->str, "=") == 0)
		return (0);
	if ((current->type == WORD_D_QUOTES || current->type == WORD_S_QUOTES)
		&& (next->type == WORD || next->type == WORD_D_QUOTES
			|| next->type == WORD_S_QUOTES))
		return (1);
	if (current->type == WORD && (next->type == WORD_D_QUOTES
			|| next->type == WORD_S_QUOTES))
		return (1);
	return (0);
}

int	join_quoted_tokens(t_struct *current)
{
	t_struct	*temp;
	char		*joined_str;
	char		*old_str;

	if (!(can_join_tokens(current, current->next)))
		return (0);
	joined_str = ft_strjoin(current->str, current->next->str);
	if (!joined_str)
		return (0);
	old_str = current->str;
	current->str = joined_str;
	free(old_str);
	temp = current->next;
	current->next = temp->next;
	free(temp->str);
	temp->str = NULL;
	return (1);
}

int	process_fusion_iteration(t_struct *data)
{
	t_struct	*current;
	int			fused;

	fused = 0;
	current = data;
	while (current && current->next)
	{
		if (current->type == SPACES)
		{
			current = current->next;
			continue ;
		}
		if (current->next->type == SPACES)
		{
			current = current->next;
			continue ;
		}
		if (join_quoted_tokens(current))
		{
			fused = 1;
			continue ;
		}
		current = current->next;
	}
	return (fused);
}

void	fusion_tokens_loop(t_struct *data)
{
	int	fused;

	fused = 1;
	while (fused)
		fused = process_fusion_iteration(data);
}

void	echo_fusion(t_struct *data)
{
	t_struct	*current;

	if (!data)
		return ;
	fusion_tokens_loop(data);
	current = data;
	while (current)
	{
		if (current->type != NONE && (current->type == WORD
				|| current->type == WORD_D_QUOTES
				|| current->type == WORD_S_QUOTES))
			clean_quotes(current);
		current = current->next;
	}
}
