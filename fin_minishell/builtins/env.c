/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:08 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/06/18 15:36:50 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_exec *exec, t_struct *data, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd("‘", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("‘", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exec->last_status = 125;
		return (0);
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	exec->last_status = 0;
	return (1);
}
