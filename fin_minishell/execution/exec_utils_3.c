/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:19:28 by fbenkaci          #+#    #+#             */
/*   Updated: 2026/06/18 17:02:29 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static int	try_path(t_exec *exec, char *dossier, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dossier, "/");
	if (!tmp)
		return (0);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (0);
	if (access(full_path, X_OK) == 0)
	{
		exec->path = full_path;
		return (1);
	}
	free(full_path);
	return (0);
}

int	split_path(t_exec *exec, char *path, char *cmd)
{
	char	**dossier;
	int		i;
	// int		found;

	i = 0;
	// found = 0;
	dossier = ft_split(path, ':');
	if (!dossier)
		return (0);
	while (dossier[i])
	{
		if (try_path(exec, dossier[i], cmd))
		{
			ft_free_array(dossier);
			return (1);
		}
		i++;
	}
	ft_free_array(dossier);
	print_cmd_not_found(cmd);
	return (0);
}

char	*search_path(char **env)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

int	validate_and_set_cmd_path(t_struct *data, t_exec *exec, char *cmd)
{
	struct stat	sb;

	if (stat(cmd, &sb) == -1)
		return (handle_cmd_error(cmd), 0);
	if (S_ISDIR(sb.st_mode))
	{
		errno = EISDIR;
		handle_cmd_error(cmd);
		return (0);
	}
	if (access(cmd, F_OK) == -1 || access(cmd, X_OK) == -1)
	{
		handle_cmd_error(cmd);
		exec->last_status = 126;
		return (0);
	}
	if (ft_strcmp(cmd, "./minishell") == 0)
	{
		if (!search_shlvl(data))
			return (0);
	}
	exec->path = ft_strdup(cmd);
	if (!exec->path)
		return (0);
	return (1);
}

int	command_loc(t_struct *data, t_exec *exec, char *cmd)
{
	char	*path;

	exec->path = NULL;
	if (is_path(cmd))
	{
		if (!validate_and_set_cmd_path(data, exec, cmd))
			return (0);
		return (1);
	}
	path = search_path(data->env);
	if (!path)
	{
		errno = ENOENT;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	if (!split_path(exec, path, cmd))
		return (0);
	return (1);
}
