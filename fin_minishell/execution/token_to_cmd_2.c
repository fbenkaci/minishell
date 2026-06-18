/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:00:16 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:00:44 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	handle_in(t_struct **cur, t_cmd *cmd)
{
	t_redir	*new_redir;

	if ((*cur)->next)
	{
		*cur = (*cur)->next;
		while (*cur && (*cur)->type == SPACES)
			*cur = (*cur)->next;
		if (!*cur)
			return (-1);
		if (!(*cur)->str || (*cur)->str[0] == '\0')
		{
			ft_putstr_fd("minishell: : No such file or directory\n", 2);
			return (-1);
		}
		new_redir = create_redir_node((*cur)->str, 0);
		if (!new_redir)
			return (-1);
		add_infile_to_list(cmd, new_redir, (*cur)->str);
		if (!cmd->infile)
			return (-1);
		return (1);
	}
	return (0);
}

int	handle_out(t_struct **cur, t_cmd *cmd, int fd)
{
	t_redir	*new_redir;

	(void)fd;
	if ((*cur)->next)
	{
		*cur = (*cur)->next;
		while (*cur && (*cur)->type == SPACES)
			*cur = (*cur)->next;
		if (!*cur)
			return (-1);
		if (!(*cur)->str || (*cur)->str[0] == '\0')
		{
			ft_putstr_fd("minishell: : No such file or directory\n", 2);
			return (-1);
		}
		new_redir = create_redir_node((*cur)->str, 0);
		if (!new_redir)
			return (-1);
		add_outfile_to_list(cmd, new_redir, (*cur)->str);
		cmd->append = 0;
		if (!cmd->outfile)
			return (-1);
	}
	return (1);
}

int	handle_out_and_in(t_struct **cur, t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (*cur && (*cur)->type == REDIR_OUT)
	{
		if (handle_out(cur, cmd, fd) == -1)
			return (-1);
		if ((*cur)->next)
			*cur = (*cur)->next;
		return (1);
	}
	else if (*cur && (*cur)->type == REDIR_IN)
		if (handle_in(cur, cmd) == -1)
			return (-1);
	return (0);
}

int	handle_word_and_expand(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	if (*cur && ((*cur)->type == WORD || (*cur)->type == WORD_D_QUOTES
			|| (*cur)->type == WORD_S_QUOTES || (*cur)->type == EMPTY_QUOTES))
	{
		if ((*cur)->next && (*cur)->next->type == WORD && (*cur)->next->str
			&& ft_strcmp((*cur)->next->str, "=") == 0 && ((!(*cur)->next->next)
				|| ((*cur)->next->next && ((*cur)->next->next->type == WORD
						|| (*cur)->next->next->type == WORD_D_QUOTES
						|| (*cur)->next->next->type == WORD_S_QUOTES
						|| (*cur)->next->next->type == EMPTY_QUOTES))))
			return (handle_variable_assignment(cur, cmd, i, envp));
		if (ft_strchr((*cur)->str, '$') && (*cur)->type != WORD_S_QUOTES)
		{
			if (process_variable_expansion2(cur, cmd, i, envp) == -1)
				return (-1);
			return (1);
		}
		else
		{
			cmd->argv[*i] = ft_strdup((*cur)->str);
			if (!cmd->argv[*i])
				return (-1);
		}
		(*i)++;
	}
	return (1);
}

int	handle_word_and_append(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	if (*cur && (*cur)->type == APPEND)
	{
		if ((*cur)->next)
		{
			if (handle_append_redirection(cur, cmd) == -1)
				return (-1);
		}
	}
	else if (*cur && ((*cur)->type == WORD || (*cur)->type == WORD_D_QUOTES
			|| (*cur)->type == WORD_S_QUOTES
			|| (*cur)->type == EMPTY_QUOTES))
	{
		if (handle_word_and_expand(cur, cmd, i, envp) == -1)
			return (-1);
	}
	return (1);
}
