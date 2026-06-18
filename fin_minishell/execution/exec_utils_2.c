/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:02:08 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:02:09 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	ft_lstsize_bis(t_cmd *cmd)
{
	int	nbr_element;

	if (!cmd)
		return (-1);
	nbr_element = 0;
	while (cmd)
	{
		nbr_element++;
		cmd = cmd->next;
	}
	return (nbr_element);
}

void	close_pipes(t_exec *data, int index, int i, int j)
{
	int	should_close;

	should_close = 0;
	if (index == 0)
	{
		should_close = (i != index || j != 1);
	}
	else if (index == data->nb_cmds - 1)
	{
		should_close = (i != index - 1 || j != 0);
	}
	else
	{
		should_close = ((i != index - 1 || j != 0) && (i != index || j != 1));
	}
	if (data->pipes && i < data->nb_cmds - 1)
	{
		if (should_close && data->pipes[i][j] != -1)
		{
			close(data->pipes[i][j]);
			data->pipes[i][j] = -1;
		}
	}
}

void	close_unused_pipes(t_exec *data, int index)
{
	int	i;
	int	j;

	if (!data || !data->pipes)
		return ;
	i = 0;
	while (i < data->nb_cmds - 1)
	{
		j = 0;
		while (j < 2)
		{
			close_pipes(data, index, i, j);
			j++;
		}
		i++;
	}
}

int	caculate_nb_cmd(t_exec *data, t_cmd *cmd)
{
	if (!cmd)
		return (-1);
	data->nb_cmds = ft_lstsize_bis(cmd);
	return (1);
}

// Fonction pour libérer tout depuis le processus parent (inclut le token pool)
void	free_all_shell_parent(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	if (cmd)
		free_all_cmd(cmd);
	if (*data)
	{
		if ((*data)->token_pool)
			free_token_pool((*data)->token_pool);
		free_tokens((*data));
	}
	if (exec->pipes != NULL)
		free(exec->pipes);
	if (exec->path)
		free(exec->path);
	free(exec);
}
