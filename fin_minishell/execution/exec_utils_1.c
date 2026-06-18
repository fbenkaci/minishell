/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:01:28 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/08 15:09:27 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	setup_pipe_redirections(t_exec *exec, int index, t_cmd *cmd)
{
	if (!exec || !exec->pipes)
		return ;
	if (index > 0 && index - 1 < exec->nb_cmds - 1)
	{
		dup2(exec->pipes[index - 1][0], STDIN_FILENO);
		close(exec->pipes[index - 1][0]);
	}
	if (!cmd->outfile && index < exec->nb_cmds - 1)
	{
		dup2(exec->pipes[index][1], STDOUT_FILENO);
		close(exec->pipes[index][1]);
	}
}

void	handle_exec_error(t_struct **data, t_exec *exec, t_cmd *cmd_list)
{
	if (errno == ENOENT)
	{
		exec->last_status = 127;
		free_all_cmd(cmd_list);
		free_all_shell(data, exec, NULL);
		exit(127);
	}
	else if (errno == EACCES)
	{
		exec->last_status = 126;
		free_all_cmd(cmd_list);
		free_all_shell(data, exec, NULL);
		exit(126);
	}
	free_all_cmd(cmd_list);
	free_all_shell(data, exec, NULL);
	exit(126);
}

static void	run_external_command(t_struct **data, t_exec *exec, t_cmd *cmd,
		t_cmd *cmd_list)
{
	if (!command_loc(*data, exec, cmd->argv[0]))
	{
		exec->last_status = 126;
		handle_exec_error(data, exec, cmd_list);
	}
	execve(exec->path, cmd->argv, (*data)->env);
	handle_cmd_error(cmd->argv[0]);
	handle_exec_error(data, exec, cmd_list);
}

void	run_command(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	t_cmd	*cmd_list;

	cmd_list = exec->cmds;
	if (!cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		exec->last_status = 0;
		free_all_cmd(cmd_list);
		free_all_shell(data, exec, NULL);
		exit(0);
	}
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(exec, *data, cmd);
		free_all_cmd(cmd_list);
		free_all_shell(data, exec, NULL);
		exit(0);
	}
	run_external_command(data, exec, cmd, cmd_list);
}

int	fork_and_execute_commands(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (cmd)
	{
		exec->pids = fork();
		if (exec->pids == -1)
			return (perror("minishell: fork"), -1);
		if (exec->pids == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			close_unused_pipes(exec, index);
			if (index > 0 || !cmd->outfile)
				setup_pipe_redirections(exec, index, cmd);
			if (cmd->outfile && index < exec->nb_cmds - 1 && exec->pipes)
				close(exec->pipes[index][1]);
			setup_redirections(*data, cmd, exec);
			run_command(data, exec, cmd);
		}
		index++;
		cmd = cmd->next;
	}
	return (1);
}
