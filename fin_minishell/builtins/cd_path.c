/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:30:40 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/01 15:44:32 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_all(char *new_pwd, char *oldpwd, char *env_old, char *env_new)
{
	if (new_pwd)
		free(new_pwd);
	if (oldpwd)
		free(oldpwd);
	if (env_old)
		free(env_old);
	if (env_new)
		free(env_new);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	try_change_directory(const char *path, char *old_pwd)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		free(old_pwd);
		return (0);
	}
	return (1);
}

int	cd_path(t_struct *data, const char *path)
{
	char		*old_pwd;
	struct stat	path_stat;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (0);
	if (stat(path, &path_stat) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (free(old_pwd), 0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		return (free(old_pwd), 0);
	}
	if (!try_change_directory(path, old_pwd))
		return (0);
	if (!update_pwd_vars(data, old_pwd))
		return (0);
	return (1);
}

char	*add_env_var(t_struct *data, char *var, char *new_val_var)
{
	char	**new_env;
	char	*new_string;
	int		len;
	int		i;

	len = 0;
	while (data->env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_string = ft_strjoin(var, new_val_var);
	if (!new_string)
		return (free(new_env), NULL);
	new_env[len] = new_string;
	new_env[len + 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (new_string);
}
