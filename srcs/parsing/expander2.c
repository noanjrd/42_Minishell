/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:34:09 by naankour          #+#    #+#             */
/*   Updated: 2025/06/02 14:34:09 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_env_var(char **str, t_env *env, int *len)
{
	char	*name;
	char	*value;
	int		i;

	name = malloc(ft_strlen(*str) + 1);
	if (!name)
		return (1);
	i = 0;
	while (ft_isalnum(**str) || **str == '_')
		name[i++] = *(*str)++;
	name[i] = '\0';
	value = ft_copy(ft_search_value(env, name));
	if (value)
		*len += ft_strlen(value);
	free(value);
	free(name);
	return (0);
}

int	handle_exit_code(char **str, int exit_code, int *len)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(exit_code);
	*len += ft_strlen(exit_code_str);
	free(exit_code_str);
	(*str)++;
	return (0);
}

int	get_token_length(char *str, t_env *env, int exit_code)
{
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
				handle_exit_code(&str, exit_code, &len);
			else if (*str == '\0' || *str == ' ' || !ft_isalnum(*str))
				len++;
			else
				handle_env_var(&str, env, &len);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

char	*ft_malloc_final_buffer(char *str, t_env *env, int exit_code)
{
	char	*final_buffer;

	final_buffer = malloc (get_token_length(str, env, exit_code) + 1);
	if (!final_buffer)
		return (NULL);
	return (final_buffer);
}

char	*new_token_value(char *str, t_data	*data)
{
	t_str	src;
	char	*final_buffer;
	int		j;

	final_buffer = ft_malloc_final_buffer(str, data->env, data->exit_code);
	if (!final_buffer)
		return (NULL);
	src = (t_str){str, 0};
	j = 0;
	while (str[src.i])
		j = ft_handle_dollar(&src, final_buffer, j, data);
	final_buffer[j] = '\0';
	return (final_buffer);
}
