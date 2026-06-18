/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:27:21 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/07 17:46:03 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

/* Gère les redirections de sortie */
void	handle_output_redirs(t_struct *data, t_cmd *cmd, t_exec *exec)
{
	if (!cmd->outfiles)
		return ;
	if (handle_multiple_outfiles(data, cmd, exec) == -1)
		exit(1);
}

/* Gère le heredoc seul ou combiné */
void	handle_heredoc_redirs(t_cmd *cmd)
{
	int	fd;

	if (cmd->infiles || cmd->infile)
	{
		fd = create_combined_input(cmd);
		if (fd >= 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
}

/* Gère les fichiers d'entrée simples ou multiples */
void	handle_file_redirs(t_struct *data, t_cmd *cmd, t_exec *exec)
{
	int	fd;

	if (cmd->infiles)
	{
		if (handle_multiple_infiles(data, cmd, exec) == -1)
			exit(1);
	}
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			handle_cmd_error(cmd->infile);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

/* Point d'entrée pour configurer toutes les redirections */
void	setup_redirections(t_struct *data, t_cmd *cmd, t_exec *exec)
{
	handle_output_redirs(data, cmd, exec);
	if (cmd->heredoc)
		handle_heredoc_redirs(cmd);
	else
		handle_file_redirs(data, cmd, exec);
}

void	free_all_shell(t_struct **data, t_exec *exec, t_cmd *cmd)
{
	if (cmd)
		free_all_cmd(cmd);
	if (*data)
	{
		if ((*data)->env)
			ft_free_array((*data)->env);
		if ((*data)->str)
			free((*data)->str);
		if ((*data)->token_pool)
			free_token_pool((*data)->token_pool);
		free(*data);
	}
	if (exec)
	{
		if (exec->pipes != NULL)
			free(exec->pipes);
		if (exec->path)
			free(exec->path);
		free(exec);
	}
}
