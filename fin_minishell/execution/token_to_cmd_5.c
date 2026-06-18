/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:56:42 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:58:14 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static char	*expand_assignment_value(t_struct **cur, char **envp)
{
	t_struct	temp_node;
	t_struct	*temp_ptr;
	char		*expanded_value;

	if (!ft_strchr((*cur)->next->next->str, '$'))
		return ((*cur)->next->next->str);
	if ((*cur)->next->next->type == WORD_S_QUOTES)
		return ((*cur)->next->next->str);
	temp_node.str = ft_strdup((*cur)->next->next->str);
	if (!temp_node.str)
		return (NULL);
	temp_node.exec = (*cur)->exec;
	temp_ptr = &temp_node;
	if (expand_variable(&temp_ptr, temp_node.str, envp) == -1)
	{
		free(temp_node.str);
		return (NULL);
	}
	expanded_value = temp_ptr->str;
	return (expanded_value);
}

static char	*create_assignment_string(t_struct **cur, char **envp)
{
	char	*temp;
	char	*expanded_value;
	char	*combined_arg;

	temp = ft_strjoin((*cur)->str, "=");
	if (!temp)
		return (NULL);
	if ((*cur)->next->next)
	{
		expanded_value = expand_assignment_value(cur, envp);
		if (!expanded_value)
			return (free(temp), NULL);
		combined_arg = ft_strjoin(temp, expanded_value);
		if (expanded_value != (*cur)->next->next->str)
			free(expanded_value);
		*cur = (*cur)->next->next;
	}
	else
	{
		combined_arg = ft_strdup(temp);
		*cur = (*cur)->next;
	}
	free(temp);
	return (combined_arg);
}

int	handle_variable_assignment(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	char	*combined_arg;

	combined_arg = create_assignment_string(cur, envp);
	if (!combined_arg)
		return (-1);
	cmd->argv[*i] = combined_arg;
	(*i)++;
	return (1);
}

int	process_variable_expansion2(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	if (expand_variable(cur, (*cur)->str, envp) == -1)
		return (-1);
	if ((*cur)->str[0] == '\0')
		return (1);
	cmd->argv[*i] = ft_strdup((*cur)->str);
	if (!cmd->argv[*i])
		return (ft_free_array(cmd->argv), -1);
	(*i)++;
	return (1);
}
