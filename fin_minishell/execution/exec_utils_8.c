/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:56:11 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/09 14:27:14 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	update_shlvl(t_struct *data, int i, char *tmp)
{
	char	*res_char;
	char	*final;
	int		res;
	int		j;

	final = NULL;
	res = 0;
	j = 6;
	while (data->env[i][j])
		res = res * 10 + data->env[i][j++] - '0';
	res += 1;
	res_char = ft_itoa(res);
	if (!res_char)
		return (0);
	final = ft_strjoin("SHLVL=", res_char);
	if (!final)
		return (free(res_char), 0);
	data->env[i] = final;
	if (!data->env[i])
		return (free(res_char), free(final), 0);
	free(tmp);
	free(res_char);
	return (1);
}

int	search_shlvl(t_struct *data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "SHLVL", 5) == 0 && data->env[i][5] == '=')
		{
			tmp = data->env[i];
			j = 6;
			while (data->env[i][j])
			{
				if (ft_isdigit(data->env[i][j]))
					j++;
				else
					return (0);
			}
			return (update_shlvl(data, i, tmp));
		}
		i++;
	}
	if (!add_in_env(data, "SHLVL=0"))
		return (0);
	return (1);
}
