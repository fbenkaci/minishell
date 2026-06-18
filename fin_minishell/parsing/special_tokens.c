/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:26:06 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 17:26:25 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_struct *start)
{
	t_struct	*tmp;

	while (start)
	{
		tmp = start;
		start = start->next;
		free(tmp->str);
		free(tmp);
	}
}

t_struct	*create_token(const char *str, int len, t_token type,
		t_struct *data)
{
	t_struct	*new;
	int			i;

	if (!data || !data->token_pool)
		return (NULL);
	new = get_token_from_pool(data->token_pool);
	if (!new)
		return (NULL);
	new->str = malloc(len + 1);
	if (!new->str)
	{
		data->token_pool->index++;
		return (NULL);
	}
	i = -1;
	while (++i, i < len)
		new->str[i] = str[i];
	new->str[i] = '\0';
	new->type = type;
	new->next = NULL;
	new->env = NULL;
	new->exec = NULL;
	new->token_pool = data->token_pool;
	return (new);
}

int	token_init(t_struct *data)
{
	int	i;

	i = 0;
	if (!data || !data->str)
		return (-1);
	data->next = NULL;
	data->type = NONE;
	while (data->str[i] && data->str[i] != ' ' && data->str[i] != '<'
		&& data->str[i] != '>' && data->str[i] != '|' && data->str[i] != '('
		&& data->str[i] != ')' && data->str[i] != '\'' && data->str[i] != '\"')
		i++;
	i = 0;
	return (i);
}

void	tokenize_string(t_struct *data, int i)
{
	t_struct	*cur;

	if (i < 0)
		return ;
	cur = data;
	while (data->str[i])
	{
		if (data->str[i] == ' ')
			handle_space_token(data->str, &i, &cur);
		else if (data->str[i] == '\"' || data->str[i] == '\'')
			handle_quotes(data->str, &i, &cur);
		else if (data->str[i] == '<' || data->str[i] == '>')
			handle_redir_token(data->str, &i, &cur);
		else if (data->str[i] == '|' || data->str[i] == '('
			|| data->str[i] == ')')
			handle_special_tokens(data->str, &i, &cur);
		else
			handle_word_token(data->str, &i, &cur);
		if (i >= (int)ft_strlen(data->str))
			break ;
	}
}

void	token_append(t_struct *data)
{
	int	start_index;

	start_index = token_init(data);
	if (start_index >= 0)
		tokenize_string(data, start_index);
}
