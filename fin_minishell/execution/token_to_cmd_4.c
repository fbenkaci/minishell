/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:54:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/02 15:21:24 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	handle_append_redirection(t_struct **cur, t_cmd *cmd)
{
	t_redir	*new_redir;

	if (!(*cur)->next)
		return (1);
	while (*cur && (*cur)->next && (*cur)->next->type == SPACES)
		*cur = (*cur)->next;
	if (!(*cur)->next)
		return (-1);
	if (!(*cur)->next->str || (*cur)->next->str[0] == '\0')
	{
		ft_putstr_fd("minishell: : No such file or directory\n", 2);
		return (-1);
	}
	new_redir = create_redir_node((*cur)->next->str, 1);
	if (!new_redir)
		return (-1);
	add_outfile_to_list(cmd, new_redir, (*cur)->next->str);
	cmd->append = 1;
	if (!cmd->outfile)
		return (-1);
	if ((*cur)->next)
		*cur = (*cur)->next;
	return (1);
}

t_struct	*find_redir_end(t_struct *redir_start)
{
	t_struct	*redir_end;

	redir_end = redir_start;
	while (redir_end->next)
	{
		if (redir_end->next->type == SPACES
			|| redir_end->next->type == WORD
			|| redir_end->next->type == WORD_D_QUOTES
			|| redir_end->next->type == WORD_S_QUOTES)
		{
			redir_end = redir_end->next;
			if (redir_start->type == HEREDOC && redir_end->type != SPACES)
				break ;
		}
		else
			break ;
	}
	return (redir_end);
}

int	reorder_command_tokens(t_struct **cur)
{
	t_struct	*redir_start;
	t_struct	*redir_end;
	t_struct	*cmd_node;
	t_struct	*temp;

	if (!cur || !*cur)
		return (0);
	if ((*cur)->type != HEREDOC && (*cur)->type != REDIR_OUT
		&& (*cur)->type != REDIR_IN && (*cur)->type != APPEND)
		return (0);
	redir_start = *cur;
	redir_end = find_redir_end(redir_start);
	cmd_node = redir_end->next;
	while (cmd_node && cmd_node->type == SPACES)
		cmd_node = cmd_node->next;
	if (!cmd_node)
		return (0);
	if (cmd_node->type != WORD && cmd_node->type != WORD_D_QUOTES
		&& cmd_node->type != WORD_S_QUOTES)
		return (0);
	temp = cmd_node->next;
	redir_end->next = temp;
	cmd_node->next = redir_start;
	*cur = cmd_node;
	return (1);
}

void	free_all_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
			ft_free_array(cmd->argv);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->outfiles)
			free_outfiles(cmd->outfiles);
		if (cmd->infiles)
			free_outfiles(cmd->infiles);
		if (cmd->heredoc_delim)
			free(cmd->heredoc_delim);
		if (cmd->heredoc_fd > 0)
			close(cmd->heredoc_fd);
		free(cmd);
		cmd = tmp;
	}
}
