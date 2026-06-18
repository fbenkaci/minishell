/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:18:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/26 19:18:00 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_identifier(char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (0);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (0);
	i = 1;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_likely_parsing_fragment(char *arg, char **cmd, int current_index)
{
	char	*prev_arg;

	if (!arg || current_index <= 0)
		return (0);
	prev_arg = cmd[current_index - 1];
	if (prev_arg && ft_strchr(prev_arg, '='))
		return (0);
	return (0);
}

int	should_process_export_arg(char *arg)
{
	if (!arg || !arg[0])
		return (0);
	if (ft_strchr(arg, '='))
		return (1);
	if (is_valid_identifier(arg))
		return (1);
	return (1);
}

static void	print_export_error(char *cmd)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	is_valid_export(char *cmd)
{
	char	*equal_pos;
	char	*var_name;
	int		result;

	if (!cmd || !cmd[0])
		return (0);
	equal_pos = ft_strchr(cmd, '=');
	if (equal_pos)
	{
		var_name = ft_substr(cmd, 0, equal_pos - cmd);
		if (!var_name)
			return (0);
		result = is_valid_identifier(var_name);
		free(var_name);
		if (!result)
			print_export_error(cmd);
		return (result);
	}
	result = is_valid_identifier(cmd);
	if (!result)
		print_export_error(cmd);
	return (result);
}
