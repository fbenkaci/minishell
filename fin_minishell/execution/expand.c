/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:50:39 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:29:35 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	process_variable_expansion(t_struct **cur, char *str, char **envp, int i)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;

	var_name = extract_var_name(str, i + 1);
	if (!var_name)
		return (-1);
	var_value = get_env_value_2(var_name, envp);
	if (!var_value)
	{
		new_str = replace_variable(str, i, var_name, "");
		if (!new_str)
			return (free(var_name), -1);
		free(var_name);
		return (update_current_string(cur, str, new_str));
	}
	new_str = replace_variable(str, i, var_name, var_value);
	if (!new_str)
	{
		free(var_name);
		return (-1);
	}
	free(var_name);
	return (update_current_string(cur, str, new_str));
}

int	handle_exit_status_expansion(t_struct **cur, char *current_str, int i)
{
	char	*exit_status_str;
	char	*new_str;
	int		result;

	exit_status_str = ft_itoa((*cur)->exec->last_status);
	if (!exit_status_str)
		return (-1);
	new_str = replace_variable(current_str, i, "?", exit_status_str);
	if (!new_str)
	{
		free(exit_status_str);
		return (-1);
	}
	free(exit_status_str);
	result = update_current_string(cur, current_str, new_str);
	return (result);
}

int	handle_normal_variable_expansion(t_struct **cur, char *current_str,
		char **envp, int i)
{
	int	result;

	result = process_variable_expansion(cur, current_str, envp, i);
	return (result);
}

int	process_exit_status_at_position(t_struct **cur, char *current_str, int *i)
{
	int		result;
	char	*var_value;
	int		value_len;

	result = handle_exit_status_expansion(cur, current_str, *i);
	if (result != 0)
		return (result);
	current_str = (*cur)->str;
	var_value = ft_itoa((*cur)->exec->last_status);
	if (var_value)
		value_len = ft_strlen(var_value);
	else
		value_len = 0;
	free(var_value);
	*i += value_len;
	return (0);
}

int	process_variable_at_position(t_struct **cur, char *current_str, char **envp,
		int *i)
{
	int		result;
	char	*var_name;
	char	*var_value;
	int		value_len;

	var_name = extract_var_name(current_str, *i + 1);
	if (!var_name)
		return (-1);
	var_value = get_env_value_2(var_name, envp);
	if (var_value)
		value_len = ft_strlen(var_value);
	else
		value_len = 0;
	free(var_name);
	result = handle_normal_variable_expansion(cur, current_str, envp, *i);
	if (result != 0)
		return (result);
	*i += value_len;
	return (0);
}
