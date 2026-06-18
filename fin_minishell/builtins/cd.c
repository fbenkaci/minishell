/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:47:07 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 19:49:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*update_env(t_struct *data, char *var, char *new_val_var)
{
	char	*new_string;
	int		len_var;
	int		i;

	len_var = ft_strlen(var);
	new_string = NULL;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(var, data->env[i], len_var) == 0)
		{
			new_string = ft_strjoin(var, new_val_var);
			if (!new_string)
				return (NULL);
			free(data->env[i]);
			data->env[i] = new_string;
			return (new_string);
		}
		i++;
	}
	return (add_env_var(data, var, new_val_var));
}

char	*get_env_value(t_struct *data, char *key)
{
	int		len_key;
	char	*str;
	int		i;

	len_key = ft_strlen(key);
	str = NULL;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(key, data->env[i], len_key) == 0)
		{
			str = data->env[i] + len_key;
			return (str);
		}
		i++;
	}
	return (NULL);
}

int	update_pwd_vars(t_struct *data, char *oldpwd)
{
	char	*new_pwd;
	char	*env_new;
	char	*env_old;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(oldpwd);
		return (0);
	}
	env_old = update_env(data, "OLDPWD=", oldpwd);
	env_new = update_env(data, "PWD=", new_pwd);
	if (!env_old || !env_new)
	{
		free_all(new_pwd, oldpwd, env_old, env_new);
		return (0);
	}
	free_all(new_pwd, oldpwd, NULL, NULL);
	return (1);
}

int	cd_without_arg(t_struct *data)
{
	char	*home;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 0);
	home = get_env_value(data, "HOME=");
	if (!home)
	{
		free(oldpwd);
		return (ft_putstr_fd("cd: HOME not set\n", 2), 0);
	}
	if (chdir(home) == -1)
	{
		free(oldpwd);
		return (0);
	}
	if (!update_pwd_vars(data, oldpwd))
		return (0);
	return (1);
}

int	ft_cd(t_exec *exec, t_struct *data, char **cmd)
{
	if (cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		exec->last_status = 1;
		return (0);
	}
	if (!cmd[1])
	{
		if (!cd_without_arg(data))
		{
			exec->last_status = 1;
			return (0);
		}
	}
	else if (!cd_path(data, cmd[1]))
	{
		exec->last_status = 1;
		return (0);
	}
	exec->last_status = 0;
	return (1);
}
