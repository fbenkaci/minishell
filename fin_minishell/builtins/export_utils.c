/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:56:57 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/01 17:54:23 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	add_or_replace_env_var(t_struct *data, char *cmd)
{
	char	*var_name;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (cmd[len] && cmd[len] != '=')
		len++;
	var_name = ft_substr(cmd, 0, len);
	if (!var_name)
		return (0);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, len) == 0
			&& data->env[i][len] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(cmd);
			free(var_name);
			return (1);
		}
		i++;
	}
	free(var_name);
	return (add_in_env(data, cmd));
}

int	add_in_env(t_struct *data, char *cmd)
{
	char	**cpy_env;
	int		len;
	int		i;

	len = 0;
	while (data->env[len])
		len++;
	cpy_env = malloc(sizeof(char *) * (len + 2));
	if (!cpy_env)
		return (0);
	i = 0;
	while (data->env[i])
	{
		cpy_env[i] = ft_strdup(data->env[i]);
		if (!cpy_env[i])
			return (ft_free_array(cpy_env), 0);
		i++;
	}
	cpy_env[i] = ft_strdup(cmd);
	cpy_env[i + 1] = NULL;
	ft_free_array(data->env);
	data->env = cpy_env;
	return (1);
}

void	actualize_last_status(t_exec *exec, int *flag)
{
	exec->last_status = 1;
	*flag = 1;
}
