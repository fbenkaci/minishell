/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:15:30 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/06 16:59:41 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

static void	final_cleanup(t_struct *data, t_exec *exec)
{
	clear_history();
	rl_clear_history();
	if (data)
	{
		if (data->env)
			ft_free_array(data->env);
		if (data->str)
		{
			free(data->str);
			data->str = NULL;
		}
		if (data->token_pool)
			free_token_pool(data->token_pool);
		free(data);
	}
	if (exec)
		free(exec);
}

static void	main_loop(t_struct *data, t_exec *exec)
{
	while (1)
	{
		g_signal_status = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		data->str = readline("💻 minishell > ");
		if (g_signal_status == 130)
			exec->last_status = 130;
		if (data->str == NULL)
		{
			handle_exit(data);
			break ;
		}
		if (ft_strlen(data->str) > 0 && !is_str_only_spaces(data->str))
			handle_user_line(data, exec);
		else
		{
			reset_token_pool(data->token_pool);
			data->next = NULL;
		}
		cleanup_line(data);
	}
}

static int	init_exec(t_exec **exec)
{
	*exec = malloc(sizeof(t_exec));
	if (!*exec)
		return (1);
	(*exec)->path = NULL;
	(*exec)->pipes = 0;
	(*exec)->cmds = NULL;
	(*exec)->last_status = 0;
	return (0);
}

static int	init_data(t_struct **data, t_exec *exec, char **envp)
{
	*data = malloc(sizeof(t_struct));
	if (!*data)
		return (1);
	(*data)->token_pool = init_token_pool(100);
	if (!(*data)->token_pool)
	{
		free(*data);
		return (1);
	}
	if (cpy_env(*data, envp) == -1)
	{
		free_token_pool((*data)->token_pool);
		free(*data);
		return (1);
	}
	(*data)->exec = exec;
	(*data)->next = NULL;
	(*data)->str = NULL;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	t_exec		*exec;

	(void)argv;
	data = NULL;
	exec = NULL;
	if (argc != 1)
		return (printf("Error: need only one argument\n"), 1);
	if (init_exec(&exec))
		return (1);
	if (init_data(&data, exec, envp))
	{
		free(exec);
		return (1);
	}
	main_loop(data, exec);
	final_cleanup(data, exec);
	return (0);
}
