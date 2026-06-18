/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/02 15:46:36 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, ":") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_exec *exec, t_struct *data, t_cmd *cmd)
{
	if (ft_strcmp(*cmd->argv, "echo") == 0)
		return (ft_echo(exec, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "cd") == 0)
		return (ft_cd(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "env") == 0)
		return (ft_env(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "exit") == 0)
		return (ft_exit(exec, data, cmd));
	else if (ft_strcmp(*cmd->argv, "export") == 0)
		return (ft_export(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, "pwd") == 0)
		return (ft_pwd(exec));
	else if (ft_strcmp(*cmd->argv, "unset") == 0)
		return (ft_unset(exec, data, cmd->argv));
	else if (ft_strcmp(*cmd->argv, ":") == 0)
		return (0);
	else
		return (0);
	return (1);
}
