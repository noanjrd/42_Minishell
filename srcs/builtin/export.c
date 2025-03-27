/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:48 by njard             #+#    #+#             */
/*   Updated: 2025/03/27 14:06:30 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *get_name_export(char *export)
{
	int i;
	int j;
	char *name;

	i = 0;
	while(export[i] && export[i] != '=')
	{
		i++;
	}
	name = malloc(sizeof(char) * (i - 6 + 1));
	i = 7;
	j = 0;
	while(export[i] && export[i] != '=')
	{
		name[j] = export[i];
		i++;
		j++;
	}
	name[j] = '\0';
	return (name);
	
}

static char *get_value_export(char *export)
{
	int i;
	int j;
	char *value;

	i = 0;
	j = 0;
	while(export[i] && export[i] != '=')
		i++;
	while(export[j])
		j++;
	if (i == j)
		return (NULL);
	value = malloc(sizeof(char) * (j - i + 1));
	i++;
	j = 0;
	while(export[i])
	{
		value[j] = export[i];
		i++;
		j++;
	}
	value[j] = 0;
	return (value);
}

int check_alrdy_exist(t_env *env, char *name, char *value)
{
	t_env	*copy;

	copy = env;
	while(copy)
	{
		
		if (ft_strcmp(copy->name, name) == 0)
		{
			free(copy->value);
			copy->value = value;
			return (1);
		}
		copy = copy->next;
	}
	return (0);
}

void	create_export(t_env *env, char *name, char *value)
{
	t_env *temp;
	t_env *new;

	temp = env;
	while (temp->next)
	{
		temp = temp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->value = value;
	new->next = NULL;
	temp->next = new;
	return ;
}

int	check_valid_name(char *name)
{
	int i;

	i = 0;
	while(name[i])
	{
		if (!(name[i] >= '0' && name[i] <= '9')
			&& !(name[i] >= 'a' && name[i] <= 'z')
			&& !(name[i] >= 'A' && name[i] <= 'Z') && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void init_export(char *export, t_env *env)
{
	char *name;
	char *value;

	name = get_name_export(export);
	if (check_valid_name(name) == 1)
		return;
	value = get_value_export(export);
	if (check_alrdy_exist(env, name, value) == 1)
		return ;
	create_export(env, name, value);
	return ;
}

void	display_export(t_env *env)
{
	t_env *copy;
	int	*tab;
	
	copy = env;
	int i = 0;
	while(i != 128)
	{
		copy = env;
		while(copy)
		{
			if (copy->name[0] == i)
				printf("%s=%s\n", copy->name, copy->value);
			copy = copy->next;
		}
		i++;
	}
	return ;
}
