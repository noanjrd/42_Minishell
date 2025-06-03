/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:57:03 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 16:34:50 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sort_env(t_env *env)
{
	t_env	*current;
	t_env	*min;

	min = NULL;
	current = env;
	while (current)
	{
		if (current->displayed == 0)
		{
			if (!min || ft_strcmp(current->name, min->name) < 0)
				min = current;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	if (min)
	{
		min->displayed = 1;
		if (min->value)
			printf("declare -x %s=\"%s\"\n", min->name, min->value);
		else
			printf("declare -x %s\n", min->name);
		display_export(env);
	}
}

void	display_export(t_env *env)
{
	t_env	*cpy;

	cpy = env;
	sort_env(env);
	while (cpy)
	{
		cpy->displayed = 0;
		cpy = cpy->next;
	}
	return ;
}

int	check_plus(char *export)
{
	int	i;

	i = 0;
	while (export[i] && export[i] != '=')
	{
		i++;
	}
	if (export[i - 1] == '+')
		return (1);
	return (0);
}

void	export_merge(t_env *env, char *name, char *value)
{
	t_env	*copy;
	char	*new_value;

	copy = env;
	new_value = NULL;
	while (copy)
	{
		if (ft_strcmp(copy->name, name) == 0)
		{
			new_value = ft_join(copy->value, value);
			free(copy->value);
			copy->value = new_value;
			return ;
		}
		copy = copy->next;
	}
	return ;
}

int	ft_check_first_character(char *value)
{
	if (value[0] != '_'
		&& !(value[0] >= 'a'
			&& value[0] <= 'z')
		&& !(value[0] >= 'A'
			&& value[0] <= 'Z'))
	{
		return (1);
	}
	return (0);
}
