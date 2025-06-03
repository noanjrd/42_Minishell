/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:43:06 by naankour          #+#    #+#             */
/*   Updated: 2025/06/02 14:43:06 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_var_name(t_str *src)
{
	int		start;
	int		name_len;
	char	*name;
	int		i;

	src->i++;
	start = src->i;
	name_len = 0;
	while (ft_isalnum(src->str[src->i]) || src->str[src->i] == '_')
		src->i++;
	name_len = src->i - start;
	if (name_len == 0)
		return (NULL);
	name = malloc(name_len +1);
	if (!name)
		return (NULL);
	i = 0;
	while (i < name_len)
	{
		name[i] = src->str[start + i];
		i++;
	}
	name[name_len] = '\0';
	return (name);
}

static int	ft_var_value(t_str *src, char *final_buffer, int j, t_env *env)
{
	char	*name;
	char	*value;
	int		k;

	name = extract_var_name(src);
	if (!name)
		return (j);
	value = ft_copy(ft_search_value(env, name));
	free(name);
	if (!value)
		value = ft_copy("");
	k = 0;
	while (value[k])
		final_buffer[j++] = value[k++];
	free(value);
	return (j);
}

static int	ft_exit_code(char *final_buffer, int exit_code, int j)
{
	char	*str_exit_code;
	int		k;

	str_exit_code = ft_itoa(exit_code);
	k = 0;
	while (str_exit_code[k])
		final_buffer[j++] = str_exit_code[k++];
	free(str_exit_code);
	return (j);
}

int	ft_handle_dollar(t_str *src, char *final_buffer, int j, t_data *data)
{
	if (src->str[src->i] == '$' && src->str[src->i + 1] == '?')
	{
		j = ft_exit_code(final_buffer, data->exit_code, j);
		src->i += 2;
	}
	else if ((src->str[src->i] == '$') && ((src->str[src->i + 1] == '\0')
			|| (src->str[src->i + 1] == ' ')
			|| (!ft_isalnum(src->str[src->i + 1]))))
		final_buffer[j++] = src->str[src->i++];
	else if (src->str[src->i] == '$' && ((src->str[src->i + 1] != '$')
			|| src->str[src->i] == 34))
		j = ft_var_value(src, final_buffer, j, data->env);
	else
		final_buffer[j++] = src->str[src->i++];
	return (j);
}
