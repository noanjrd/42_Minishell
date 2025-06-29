/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:48 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 17:34:49 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_name_export(char *export)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (i >= 1 && export[i - 1] == '+')
		i--;
	if (i >= 1 && export[i - 1] == '-')
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	j = 0;
	while (j < i)
	{
		name[j] = export[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

static char	*get_value_export(char *export)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (export[i] && export[i] != '=')
		i++;
	while (export[j])
		j++;
	if (i == j)
		return (NULL);
	value = malloc(sizeof(char) * (j - i + 1));
	if (!value)
		return (NULL);
	i++;
	j = 0;
	while (export[i])
	{
		value[j++] = export[i++];
	}
	value[j] = '\0';
	return (value);
}

t_token	*export_launch(t_data *data, t_env *env, t_token *token, char *export)
{
	char	*name;
	char	*value;

	name = get_name_export(export);
	if (!name || check_valid_name(name) == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(token->value, 2);
		write(2, "': not a valid identifier\n", 26);
		data->exit_code = 1;
		free(name);
		return (token->next);
	}
	value = get_value_export(export);
	if (check_alrdy_exist(env, name, value, export) == 1)
	{
		if (ft_strcmp(name, "PATH") == 0)
		{
			ft_free_tab(data->paths_system);
			initalising_path(data);
		}
		return (free(name), token->next);
	}
	create_export(data, env, name, value);
	return (token->next);
}

static int	ft_condition(t_token *token)
{
	if (token->next->type
		!= WORD && token->next->type != SINGLE_QUOTES
		&& token->next->type != DOUBLE_QUOTES)
	{
		return (1);
	}
	return (0);
}

void	ft_export(t_data *data, t_env *env, t_token *token)
{
	t_token	*token_copy;

	token_copy = token;
	if (token_copy->next && token_copy->next->type == PIPE)
		return (display_export(env));
	token_copy = token;
	if (!token_copy->next || ft_condition(token_copy) == 1)
		return (display_export(env));
	token_copy = token_copy->next;
	while (token_copy && (token_copy->type == WORD
			|| token_copy->type == SINGLE_QUOTES
			|| token_copy->type == DOUBLE_QUOTES))
	{
		token_copy = export_launch(data, env, token_copy, token_copy->value);
	}
}
