/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:23:17 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 17:29:13 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_struct *token, t_token_pool *pool)
{
	token->str = NULL;
	token->next = NULL;
	token->env = NULL;
	token->exec = NULL;
	token->token_pool = pool;
	token->type = NONE;
}

t_token_pool	*init_token_pool(int initial_capacity)
{
	t_token_pool	*pool;

	pool = malloc(sizeof(t_token_pool));
	if (!pool)
		return (NULL);
	pool->tokens = malloc(sizeof(t_struct) * initial_capacity);
	if (!pool->tokens)
	{
		free(pool);
		return (NULL);
	}
	pool->index = 0;
	pool->capacity = initial_capacity;
	return (pool);
}

void	reset_token_pool(t_token_pool *pool)
{
	int	i;

	if (!pool)
		return ;
	i = 0;
	while (i < pool->index)
	{
		if (pool->tokens[i].str)
		{
			free(pool->tokens[i].str);
			pool->tokens[i].str = NULL;
		}
		i++;
	}
	pool->index = 0;
}

void	free_token_pool(t_token_pool *pool)
{
	if (!pool)
		return ;
	reset_token_pool(pool);
	if (pool->tokens)
		free(pool->tokens);
	free(pool);
}

void	free_token_strings_only(t_token_pool *pool)
{
	int	i;

	i = 0;
	if (!pool)
		return ;
	while (i < pool->index)
	{
		if (pool->tokens[i].str)
		{
			free(pool->tokens[i].str);
			pool->tokens[i].str = NULL;
		}
		i++;
	}
}
