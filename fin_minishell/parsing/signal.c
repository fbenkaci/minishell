/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:28:32 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 17:28:36 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_sigint_exec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal_status = 130;
}

t_struct	*get_token_from_pool(t_token_pool *pool)
{
	t_struct	*new_tokens;
	int			new_capacity;
	int			i;
	t_struct	*token;

	if (!pool)
		return (NULL);
	if (pool->index >= pool->capacity)
	{
		new_capacity = pool->capacity * 2;
		new_tokens = malloc(sizeof(t_struct) * new_capacity);
		if (!new_tokens)
			return (NULL);
		i = -1;
		while (++i, i < pool->index)
		{
			new_tokens[i] = pool->tokens[i];
		}
		free(pool->tokens);
		pool->tokens = new_tokens;
		pool->capacity = new_capacity;
	}
	token = &pool->tokens[pool->index++];
	init_token(token, pool);
	return (token);
}
