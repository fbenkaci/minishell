/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:26:10 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/07 20:00:59 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	open_all_heredocs(t_exec *exec, t_struct **data, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			tmp->heredoc_fd = heredoc_input(data, tmp->heredoc_delim);
			if (g_signal_status == 130)
			{
				exec->last_status = 130;
				return (130);
			}
			if (tmp->heredoc_fd < 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

/* Helper to handle input redirection and heredoc setup */
int	setup_input(t_cmd *cmd, int *saved_stdin)
{
	int	combined_fd;

	*saved_stdin = 0;
	if (cmd->heredoc && (cmd->infiles || cmd->infile))
	{
		*saved_stdin = dup(STDIN_FILENO);
		combined_fd = create_combined_input(cmd);
		if (combined_fd >= 0)
		{
			dup2(combined_fd, STDIN_FILENO);
			close(combined_fd);
		}
		else
			return (-1);
	}
	else if (cmd->heredoc)
	{
		*saved_stdin = dup(STDIN_FILENO);
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	return (0);
}

/* Helper to restore stdin and cleanup heredoc */
int	restore_input(t_cmd *cmd, int saved_stdin)
{
	if (saved_stdin > 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (cmd->heredoc_delim)
	{
		free(cmd->heredoc_delim);
	}
	return (0);
}

/* Main execution of a single builtin */
int	execute_single_builtin(t_exec *exec, t_cmd *cmd, t_struct **data)
{
	int	saved_stdin;
	int	builtin_status;

	if (setup_input(cmd, &saved_stdin) != -1)
		setup_input(cmd, &saved_stdin);
	builtin_status = exec_builtin(exec, *data, cmd);
	if (builtin_status == 1 && cmd->heredoc)
	{
		restore_input(cmd, saved_stdin);
	}
	return (builtin_status);
}
