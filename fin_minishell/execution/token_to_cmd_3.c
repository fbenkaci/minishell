/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:58:46 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:57:34 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	handle_heredocs(t_struct **cur, t_cmd *cmd)
{
	cmd->heredoc = 1;
	while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
		*cur = (*cur)->next;
	if ((*cur)->next->type == WORD || (*cur)->next->type == WORD_D_QUOTES
		|| (*cur)->next->type == WORD_S_QUOTES)
		*cur = (*cur)->next;
	cmd->heredoc_delim = ft_strdup((*cur)->str);
	if (!cmd->heredoc_delim)
		return (-1);
	return (1);
}

void	add_infile_to_list(t_cmd *cmd, t_redir *new_redir, char *filename)
{
	t_redir	*current;

	if (!cmd->infiles)
		cmd->infiles = new_redir;
	else
	{
		current = cmd->infiles;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(filename);
}

void	add_outfile_to_list(t_cmd *cmd, t_redir *new_redir, char *filename)
{
	t_redir	*current;

	if (!cmd->outfiles)
		cmd->outfiles = new_redir;
	else
	{
		current = cmd->outfiles;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(filename);
}
