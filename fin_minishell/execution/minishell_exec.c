/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:03:46 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:55:44 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	prepare_execution(t_cmd *cmd, t_exec *exec, t_struct **data)
{
	int	builtin_ret;
	int	heredoc_status;

	exec->cmds = cmd;
	heredoc_status = open_all_heredocs(exec, data, cmd);
	if (heredoc_status == 130)
		return (130);
	if (heredoc_status == -1)
		return (-1);
	if (caculate_nb_cmd(exec, cmd) == -1)
		return (ft_putstr_fd("Error calculating number of commands\n", 2), -1);
	if (!cmd->argv[0])
	{
		exec->last_status = 0;
		return (0);
	}
	if (exec->nb_cmds == 1 && is_builtin(cmd->argv[0]) && !cmd->outfile
		&& !cmd->infile && !cmd->outfiles && !cmd->infiles)
	{
		builtin_ret = execute_single_builtin(exec, cmd, data);
		if (builtin_ret == 0)
			return (-1);
		return (2);
	}
	return (1);
}

static int	handle_execution_signals_and_cleanup(t_exec *exec)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close_pipes_and_wait(exec);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	free(exec->pipes);
	exec->pipes = NULL;
	return (1);
}

int	execution(t_cmd *cmd, t_exec *exec, t_struct **data)
{
	int	prep_result;

	prep_result = prepare_execution(cmd, exec, data);
	if (prep_result == 130)
		return (1);
	if (prep_result == -1)
		return (-1);
	if (prep_result == 0 || prep_result == 2)
		return (1);
	if (create_pipe(exec) == -1)
	{
		exec->pipes = NULL;
		return (ft_putstr_fd("Error creating pipes\n", 2), -1);
	}
	if (fork_and_execute_commands(data, exec, cmd) == -1)
	{
		ft_putstr_fd("Error executing commands\n", 2);
		return (-1);
	}
	return (handle_execution_signals_and_cleanup(exec));
}
