/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:30:06 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 19:03:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

// Fonction pour initialiser le buffer de résultat
char	*init_result_buffer(int line_len)
{
	char	*result;
	int		result_len;

	result_len = line_len * 2;
	result = malloc(result_len);
	return (result);
}

// Fonction pour redimensionner le buffer si nécessaire
int	resize_buffer_if_needed(t_expand_data *data)
{
	char	*new_result;
	int		i;

	if (data->j >= data->result_len - 1)
	{
		data->result_len *= 2;
		new_result = malloc(data->result_len);
		if (!new_result)
			return (0);
		i = 0;
		while (i < data->j)
		{
			new_result[i] = data->result[i];
			i++;
		}
		free(data->result);
		data->result = new_result;
	}
	return (1);
}

int	init_heredoc_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (1);
}
