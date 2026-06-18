/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:58:37 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 20:02:25 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	copy_env_excluding(t_struct *data, char **new_env, char *var_name)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(var_name);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!(ft_strncmp(data->env[i], var_name, len) == 0
				&& data->env[i][len] == '='))
			new_env[j++] = data->env[i];
		else
			free(data->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
}

int	ft_unset(t_exec *exec, t_struct *data, char **cmd)
{
	char	*var_name;
	char	**new_env;
	int		len;
	int		i;

	i = 1;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
	{
		len = 0;
		var_name = cmd[i];
		while (data->env[len])
			len++;
		new_env = malloc(sizeof(char *) * (len + 1));
		if (!new_env)
			return (0);
		copy_env_excluding(data, new_env, var_name);
		i++;
	}
	exec->last_status = 0;
	return (1);
}

int	create_default_env(t_struct *data)
{
	char	*cwd;
	int		i;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	data->env = malloc(sizeof(char *) * 5);
	if (!data->env)
		return (free(cwd), -1);
	data->env[i++] = ft_strjoin("PWD=", cwd);
	if (!data->env[i - 1])
		return (free(cwd), ft_free_array(data->env), -1);
	data->env[i++] = ft_strjoin("OLDPWD=", cwd);
	if (!data->env[i - 1])
		return (free(cwd), ft_free_array(data->env), -1);
	data->env[i++] = ft_strdup("SHLVL=1");
	if (!data->env[i - 1])
		return (free(cwd), ft_free_array(data->env), -1);
	data->env[i++] = ft_strdup("_=/usr/bin/env");
	if (!data->env[i - 1])
		return (free(cwd), ft_free_array(data->env), -1);
	data->env[4] = NULL;
	return (free(cwd), 1);
}

int	copy_existing_env(t_struct *data, char **envp)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (envp[len])
		len++;
	data->env = malloc(sizeof(char *) * (len + 1));
	if (!data->env)
		return (-1);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (ft_free_array(data->env), -1);
		i++;
	}
	data->env[len] = NULL;
	return (1);
}

int	cpy_env(t_struct *data, char **envp)
{
	if (!envp || !*envp)
		return (create_default_env(data));
	return (copy_existing_env(data, envp));
}
