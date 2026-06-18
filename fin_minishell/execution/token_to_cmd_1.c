/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:04:41 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 20:11:26 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

#define MAX_ARGS 100

int	process_single_token(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	int	res;

	if ((*cur)->type == REDIR_OUT || (*cur)->type == REDIR_IN)
	{
		res = handle_out_and_in(cur, cmd);
		if (res == -1)
			return (-1);
	}
	else if ((*cur)->type == APPEND || (*cur)->type == WORD
		|| (*cur)->type == WORD_D_QUOTES || (*cur)->type == WORD_S_QUOTES
		|| (*cur)->type == EMPTY_QUOTES)
	{
		if ((*cur)->type == EMPTY_QUOTES && *i == 0)
			return (ft_putstr_fd("minishell: : command not found\n", 2), -1);
		if (handle_word_and_append(cur, cmd, i, envp) == -1)
			return (-1);
	}
	else if ((*cur)->type == HEREDOC)
	{
		if (handle_heredocs(cur, cmd) == -1)
			return (-1);
	}
	return (1);
}

int	fill_cmd_from_token(t_struct **cur, t_cmd *cmd, int *i, char **envp)
{
	int	res;

	while (*cur && (*cur)->type != PIPE)
	{
		res = process_single_token(cur, cmd, i, envp);
		if (res == -1)
			return (-1);
		*cur = (*cur)->next;
	}
	return (1);
}

t_cmd	*init_new_cmd(t_struct **cur, char **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->heredoc_delim = NULL;
	cmd->outfile = NULL;
	cmd->infile = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->next = NULL;
	cmd->heredoc = 0;
	cmd->append = 0;
	cmd->heredoc_fd = 0;
	if ((*cur))
		(*cur)->env = env;
	cmd->argv = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	ft_memset(cmd->argv, 0, sizeof(char *) * (MAX_ARGS + 1));
	return (cmd);
}

int	create_cmd_list(t_struct **cur, t_cmd *cmd, char **envp)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	while (*cur)
	{
		i = 0;
		if (fill_cmd_from_token(cur, current, &i, (*cur)->env) == -1)
			return (-1);
		current->argv[i] = NULL;
		if (*cur && (*cur)->type == PIPE)
		{
			if ((*cur)->next)
				*cur = (*cur)->next;
			current->next = init_new_cmd(cur, envp);
			if (!current->next)
				return (-1);
			current = current->next;
		}
	}
	return (1);
}

t_cmd	*create_cmd_from_tokens(t_struct **cur, char **env, t_exec *exec)
{
	t_cmd		*cmd;
	t_struct	*tmp;

	reorder_command_tokens(cur);
	cmd = init_new_cmd(cur, env);
	if (!cmd)
		return (NULL);
	tmp = *cur;
	while (tmp)
	{
		tmp->exec = exec;
		tmp = tmp->next;
	}
	if ((*cur))
	{
		if (create_cmd_list(cur, cmd, (*cur)->env) == -1)
		{
			free_all_cmd(cmd);
			return (NULL);
		}
	}
	return (cmd);
}
