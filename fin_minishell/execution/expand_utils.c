/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:12:39 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/01 17:35:17 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

// Fonction pour extraire le nom de variable après $
char	*extract_var_name(char *str, int start)
{
	int		i;
	int		len;
	char	*var_name;

	i = start;
	len = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	if (len == 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &str[start], len);
	var_name[len] = '\0';
	return (var_name);
}

int	calculate_new_length(char *str, char *var_name, char *var_value)
{
	int	original_len;
	int	var_name_len;
	int	var_value_len;
	int	new_len;

	original_len = ft_strlen(str);
	var_name_len = ft_strlen(var_name);
	if (var_value)
		var_value_len = ft_strlen(var_value);
	else
		var_value_len = 0;
	new_len = original_len - var_name_len - 1 + var_value_len;
	return (new_len);
}

int	copy_before_dollar(char *new_str, char *str, char dollar_pos)
{
	int	i;

	i = 0;
	while (i < dollar_pos)
	{
		new_str[i] = str[i];
		i++;
	}
	return (i);
}

int	copy_variable_value(char *var_value, char *new_str, int start_pos)
{
	int	i;
	int	j;

	i = start_pos;
	j = 0;
	if (var_value)
	{
		while (var_value[j])
		{
			new_str[i] = var_value[j];
			i++;
			j++;
		}
	}
	return (i);
}

// Fonction pour remplacer une variable dans une chaîne
char	*replace_variable(char *str, int dollar_pos, char *var_name,
		char *var_value)
{
	char	*new_str;
	int		i;
	int		j;
	int		new_len;
	int		var_name_len;

	new_len = calculate_new_length(str, var_name, var_value);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	i = copy_before_dollar(new_str, str, dollar_pos);
	i = copy_variable_value(var_value, new_str, i);
	var_name_len = ft_strlen(var_name);
	j = dollar_pos + var_name_len + 1;
	while (str[j])
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}
