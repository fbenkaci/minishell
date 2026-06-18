/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:19:07 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/06 16:27:58 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_all_data(t_struct *data)
{
	if (data->token_pool)
	{
		reset_token_pool(data->token_pool);
		data->next = NULL;
	}
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
}

void	handle_exit(t_struct *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	reset_token_pool(data->token_pool);
	data->next = NULL;
}

void	cleanup_line(t_struct *data)
{
	free(data->str);
	data->str = NULL;
}

static void	handle_cmd_success(t_cmd *cmd, t_struct *data, t_exec *exec)
{
	execution(cmd, exec, &data);
	free_all_cmd(cmd);
	reset_token_pool(data->token_pool);
	data->next = NULL;
	if (g_signal_status == 130)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_user_line(t_struct *data, t_exec *exec)
{
	t_cmd	*cmd;

	add_history(data->str);
	if (parsing(data))
	{
		cmd = create_cmd_from_tokens(&data->next, data->env, exec);
		if (!cmd)
		{
			reset_token_pool(data->token_pool);
			data->next = NULL;
		}
		else
			handle_cmd_success(cmd, data, exec);
	}
	else
	{
		reset_token_pool(data->token_pool);
		data->next = NULL;
	}
}
