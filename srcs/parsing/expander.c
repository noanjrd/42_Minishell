/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:36:38 by naankour          #+#    #+#             */
/*   Updated: 2025/05/05 13:36:38 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_token_lenght(char *str, t_env *env)
{
	int		i;
	int		len;
	char	*value;
	char	name[128];

	len = 0;
	while (*str)
	{
		i = 0;
		if (*str == '$')
		{
			str++;
			while (ft_isalnum(*str) || *str == '_')
				name[i++] = *str++;
			name[i] = '\0';
			value = ft_copy(ft_search_value(env, name));
			if (value)
				len = len + ft_strlen(value);
			free (value);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

char	*ft_malloc_final_buffer(char *str, t_env *env)
{
	char	*final_buffer;

	final_buffer = malloc (get_token_lenght(str, env) + 1);
	if (!final_buffer)
		return (NULL);
	return (final_buffer);
}

int	ft_exit_code(char *final_buffer, int exit_code, int j)
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

int	ft_var_value(t_str *s, char *final_buffer, int j, t_env *env)
{
	char	name[128];
	int		name_len;
	char	*value;
	int		k;

	s->i++;
	name_len = 0;
	while (ft_isalnum(s->str[s->i]) || s->str[s->i] == '_')
		name[name_len++] = s->str[s->i++];
	name[name_len] = '\0';
	value = ft_copy(ft_search_value(env, name));
	if (!value)
		value = ft_copy("");
	k = 0;
	while (value[k])
		final_buffer[j++] = value[k++];
	free(value);
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
	else if (src->str[src->i] == '$' && ft_isdigit(src->str[src->i + 1]))
		src->i += 2;
	else if ((src->str[src->i] == '$' && src->str[src->i + 1] != '$')
		|| src->str[src->i] == 34)
		j = ft_var_value(src, final_buffer, j, data->env);
	else
		final_buffer[j++] = src->str[src->i++];
	return (j);
}

char	*new_token_value(char *str, t_data	*data)
{
	t_str	src;
	char	*final_buffer;
	int		j;

	final_buffer = ft_malloc_final_buffer(str, data->env);
	if (!final_buffer)
		return (NULL);
	src = (t_str){str, 0};
	j = 0;
	while (str[src.i])
		j = ft_handle_dollar(&src, final_buffer, j, data);
	final_buffer[j] = '\0';
	return (final_buffer);
}

static int needs_expansion(t_token *token)
{
	if (!token || !token->value)
		return (0);
	if (((token->type == WORD) || (token->type == DOUBLE_QUOTES))
	&& ft_strchr(token->value, '$'))
		return (1);
	return (0);
}

static void	expand_token(t_token *token, t_data *data)
{
	char	*new_value;

	new_value = new_token_value(token->value, data);
	if (!new_value)
	{
		free(token->value);
		token->value = NULL;
		return ;
	}
	if (new_value && new_value[0] == '\0' && token->type == WORD)
	{
		free(new_value);
		free(token->value);
		token->value = NULL;
	}
	else
	{
		free(token->value);
		token->value = new_value;
	}
}

static t_token	*remove_token(t_token *token, t_token *prev, t_token *to_remove)
{
	if (!prev)
		token = to_remove->next;
	else
		prev->next = to_remove->next;
	free(to_remove->value);
	free(to_remove);
	return (token);
}

t_token *expander(t_token *token, t_data *data)
{
	t_token *current;
	t_token *prev;
	t_token *next;

	current = token;
	prev = NULL;
	while (current)
	{
		if (needs_expansion(current) == 1)
		{
			expand_token(current, data);
			if (current->value == NULL)
			{
				next = current->next;
				token = remove_token(token, prev, current);
				current = next;
				continue;
			}
		}
		prev = current;
		current = current->next;
	}
	return token;
}
