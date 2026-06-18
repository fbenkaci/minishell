/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:28:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/03 17:02:16 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

// Fonction pour extraire le nom de variable
int	extract_var_name_2(char *line, int *i, char *var_name)
{
	int	k;

	(*i)++;
	k = 0;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		var_name[k++] = line[(*i)++];
	}
	var_name[k] = '\0';
	return (k);
}

// Fonction pour copier la valeur de variable dans le résultat
int	copy_var_value(t_expand_data *data, char *var_value)
{
	int	k;

	k = 0;
	if (!var_value)
		return (1);
	while (var_value[k])
	{
		if (!resize_buffer_if_needed(data))
			return (0);
		data->result[data->j++] = var_value[k++];
	}
	return (1);
}

// Fonction pour traiter une variable trouvée
int	process_variable(t_struct **data2, char *line, int *i, t_expand_data *data)
{
	char	var_name[256];
	char	*var_value;

	extract_var_name_2(line, i, var_name);
	var_value = get_env_value_2(var_name, (*data2)->env);
	if (!copy_var_value(data, var_value))
		return (0);
	return (1);
}

// Fonction pour traiter un caractère normal
int	process_normal_char(char *line, int *i, t_expand_data *data)
{
	if (!resize_buffer_if_needed(data))
		return (0);
	data->result[data->j++] = line[(*i)++];
	return (1);
}

// Fonction principale refactorisée
char	*expand_variables_heredoc(t_struct **data2, char *line)
{
	t_expand_data	data;
	int				i;

	data.result = init_result_buffer(ft_strlen(line));
	if (!data.result)
		return (NULL);
	data.result_len = ft_strlen(line) * 2;
	data.j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i
					+ 1] == '_'))
		{
			if (!process_variable(data2, line, &i, &data))
				return (NULL);
		}
		else
		{
			if (!process_normal_char(line, &i, &data))
				return (NULL);
		}
	}
	data.result[data.j] = '\0';
	return (data.result);
}
