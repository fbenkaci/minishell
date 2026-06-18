/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:23:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/01 19:00:13 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	process_export_args(t_exec *exec, t_struct *data, char **cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (cmd[i])
	{
		if (should_process_export_arg(cmd[i])
			&& !is_likely_parsing_fragment(cmd[i], cmd, i))
		{
			if (is_valid_export(cmd[i]))
			{
				if (!add_or_replace_env_var(data, cmd[i]))
					return (exec->last_status = 1, 0);
			}
			else
				actualize_last_status(exec, &flag);
		}
		i++;
	}
	if (!flag)
		exec->last_status = 0;
	return (1);
}

int	ft_export(t_exec *exec, t_struct *data, char **cmd)
{
	if (!cmd[1])
		return (print_export(exec, data->env), 1);
	else
		return (process_export_args(exec, data, cmd));
}
