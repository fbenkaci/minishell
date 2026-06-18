/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:51:12 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 19:57:26 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_msg(char *num)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(num, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	valid_number(char *num)
{
	long long	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	if (!num[i])
	{
		i--;
		return (0);
	}
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_and_handle_arg(t_exec *exec, t_struct *data, t_cmd *cmd)
{
	long long	exit_code_ll;
	int			i;

	i = 0;
	while (cmd->argv[1][i])
	{
		if (!ft_atoll_safe(cmd->argv[1], &exit_code_ll))
		{
			error_msg(cmd->argv[1]);
			free_all_shell_parent(&data, exec, cmd);
			exit(2);
		}
		if (ft_isalpha(cmd->argv[1][i]))
		{
			exec->last_status = 2;
			error_msg(cmd->argv[1]);
			free_all_shell_parent(&data, exec, cmd);
			exit(2);
		}
		i++;
	}
	return (1);
}

void	handle_exit_final(t_exec *exec, t_struct *data, t_cmd *cmd)
{
	long long	exit_code_ll;
	int			exit_code;

	if (!valid_number(cmd->argv[1]) || !ft_atoll_safe(cmd->argv[1],
			&exit_code_ll))
	{
		error_msg(cmd->argv[1]);
		free_all_shell_parent(&data, exec, cmd);
		exit(2);
	}
	exit_code = (int)(exit_code_ll % 256);
	printf("exit\n");
	free_all_shell_parent(&data, exec, cmd);
	exit(exit_code);
}

int	ft_exit(t_exec *exec, t_struct *data, t_cmd *cmd)
{
	int	exit_code;

	if (cmd->argv[2])
	{
		validate_and_handle_arg(exec, data, cmd);
		exec->last_status = 1;
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (0);
	}
	if (!cmd->argv[1])
	{
		exit_code = exec->last_status;
		printf("exit\n");
		free_all_shell_parent(&data, exec, cmd);
		exit(exit_code);
	}
	handle_exit_final(exec, data, cmd);
	return (0);
}
