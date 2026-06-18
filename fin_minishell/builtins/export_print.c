/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:18:00 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/06/26 19:20:53 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_after_equal(char **cpy_env, int i, int j, int *flag)
{
	printf("declare -x ");
	while (cpy_env[i][j] != '\0')
	{
		if (cpy_env[i][j] == '=' && *flag == 0)
		{
			*flag = 1;
			printf("=\"");
		}
		else
			printf("%c", cpy_env[i][j]);
		j++;
	}
}

void	sorted_export(char **cpy_env)
{
	int		sorted;
	char	*tmp;
	int		i;
	int		len_env;

	len_env = 0;
	while (cpy_env[len_env])
		len_env++;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < len_env - 1)
		{
			if (ft_strcmp(cpy_env[i], cpy_env[i + 1]) > 0)
			{
				tmp = cpy_env[i];
				cpy_env[i] = cpy_env[i + 1];
				cpy_env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

void	print_export(t_exec *exec, char **cpy_env)
{
	int	flag;
	int	flag2;
	int	j;
	int	i;

	i = 0;
	sorted_export(cpy_env);
	while (cpy_env[i] != NULL)
	{
		flag2 = 0;
		if (ft_strncmp(cpy_env[i], "_=", 2) != 0)
		{
			flag2 = 1;
			flag = 0;
			j = 0;
			print_after_equal(cpy_env, i, j, &flag);
			if (flag == 1)
				printf("\"");
		}
		if (flag2 == 1)
			printf("\n");
		i++;
	}
	exec->last_status = 0;
}
