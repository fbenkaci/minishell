/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:45:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/02 15:21:24 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

t_redir	*create_redir_node(char *filename, int append)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->filename = ft_strdup(filename);
	if (!node->filename)
	{
		free(node);
		return (NULL);
	}
	node->append = append;
	node->next = NULL;
	return (node);
}

void	free_outfiles(t_redir *outfiles)
{
	t_redir	*tmp;

	while (outfiles)
	{
		tmp = outfiles;
		outfiles = outfiles->next;
		free(tmp->filename);
		free(tmp);
	}
}

int	handle_multiple_outfiles(t_struct *data, t_cmd *cmd, t_exec *exec)
{
	t_redir	*current;
	int		fd;

	(void)data;
	(void)exec;
	current = cmd->outfiles;
	while (current)
	{
		if (current->append)
			fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			handle_cmd_error(current->filename);
			return (-1);
		}
		if (current->next == NULL)
		{
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		current = current->next;
	}
	return (0);
}

int	handle_multiple_infiles(t_struct *data, t_cmd *cmd, t_exec *exec)
{
	t_redir	*current;
	int		fd;

	(void)data;
	(void)exec;
	current = cmd->infiles;
	while (current)
	{
		fd = open(current->filename, O_RDONLY);
		if (fd < 0)
		{
			handle_cmd_error(current->filename);
			return (-1);
		}
		if (current->next == NULL)
		{
			dup2(fd, STDIN_FILENO);
		}
		close(fd);
		current = current->next;
	}
	return (0);
}
