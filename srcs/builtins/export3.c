/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:01:46 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 17:34:21 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_alrdy_exist(t_env *env, char *name, char *value, char *export)
{
	t_env	*copy;

	copy = env;
	if (check_plus(export) == 1)
	{
		export_merge(env, name, value);
		return (1);
	}
	while (copy)
	{
		if (ft_strcmp(copy->name, name) == 0)
		{
			if (!value)
				return (1);
			free(copy->value);
			copy->value = value;
			return (1);
		}
		copy = copy->next;
	}
	return (0);
}

void	create_export(t_data *data, t_env *env, char *name, char *value)
{
	t_env	*temp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->value = value;
	new->displayed = 0;
	new->next = NULL;
	temp = env;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	if (ft_strcmp(name, "PATH") == 0)
	{
		ft_free_tab(data->paths_system);
		initalising_path(data);
	}
	return ;
}

int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	if (ft_check_first_character(name) == 1)
		return (1);
	i = 0;
	while (name[i])
	{
		if (!(name[i] >= '0' && name[i] <= '9')
			&& !(name[i] >= 'a' && name[i] <= 'z')
			&& !(name[i] >= 'A' && name[i] <= 'Z') && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
