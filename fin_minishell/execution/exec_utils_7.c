/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:47:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/07 18:00:31 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	close_all_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->nb_cmds - 1)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}

static void	wait_all_and_update_status(t_exec *exec)
{
	int	i;
	int	status;
	int	sig;

	status = 0;
	i = 0;
	while (i < exec->nb_cmds)
	{
		waitpid(-1, &status, 0);
		if (i == exec->nb_cmds - 1)
		{
			if (WIFEXITED(status))
				exec->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
				{
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
					exec->last_status = 128 + sig;
				}
			}
		}
		i++;
	}
}

void	close_pipes_and_wait(t_exec *exec)
{
	close_all_pipes(exec);
	wait_all_and_update_status(exec);
}

void	free_token_lis(t_struct **data)
{
	t_struct	*token_ptr;
	t_struct	*next_token;

	if (data && *data && (*data)->next)
	{
		token_ptr = (*data)->next;
		while (token_ptr)
		{
			next_token = token_ptr->next;
			if (token_ptr->str)
			{
				free(token_ptr->str);
				token_ptr->str = NULL;
			}
			free(token_ptr);
			token_ptr = next_token;
		}
		(*data)->next = NULL;
	}
}

void	complete_cleanup_and_exit(t_struct **data, t_exec *exec, t_cmd *cmd,
		int exit_code)
{
	if (cmd)
		free_all_cmd(cmd);
	free_token_lis(data);
	if (data && *data)
	{
		if ((*data)->env)
			ft_free_array((*data)->env);
		if ((*data)->str)
		{
			free((*data)->str);
			(*data)->str = NULL;
		}
		free(*data);
		*data = NULL;
	}
	if (exec)
	{
		if (exec->pipes)
			free(exec->pipes);
		if (exec->path)
			free(exec->path);
		free(exec);
	}
	exit(exit_code);
}
