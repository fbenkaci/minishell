/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:02:35 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/07/07 20:02:54 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_flag_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else if (str[i] != 'n' && str[i] != '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(t_exec *exec, char **cmd)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n' && is_flag_n(cmd[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] && cmd[i + 1][0] != '\0')
			printf(" ");
		i++;
	}
	if (flag_n == 0)
		printf("\n");
	exec->last_status = 0;
	return (1);
}
