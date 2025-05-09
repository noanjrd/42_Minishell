/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:35:47 by njard             #+#    #+#             */
/*   Updated: 2025/05/09 15:13:19 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function initializes the data structure
void	init_data(t_data *data, t_env *env)
{
	data->paths_system = NULL; 
	data->exit_code = 0;
	data->env = env;
	data->line = NULL;
	data->here_doc = 0;
	data->builtin_found = 0;
	data->fdin = malloc(100 * sizeof(int));
	initalising_path(data);
}

static char	*get_name(char *envp)
{
	int i;
	char *name;

	i = 0;
	while(envp[i] != '=')
	{
		i++;
	}
	name  = malloc((i + 1) * sizeof(char));
	i = 0;
	while(envp[i] != '=')
	{
		name[i] = envp[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char	*get_value(char *envp)
{
	int i;
	int j;
	char *value;

	i = 0;
	j = 0;
	while(envp[i] != '=')
		i++;
	while(envp[j])
		j++;
	value  = malloc((j - i + 1) * sizeof(char));
	i++;
	j = 0;
	while(envp[i])
		value[j++] = envp[i++];
	value[j] = '\0';
	return (value);
}

// This function initializes the env structure
t_env	*env_init(t_env *env, char **envp)
{
	t_env	*head;
	t_env	 *current;
	t_env *temp;
	int i;

	i = 0;
	head = env;
	env->name = get_name(envp[i]);
	env->value = get_value(envp[i]);
	env->displayed = 0;
	i++;
	while (envp[i])
	{
		current = malloc(sizeof(t_env));
		env->next = current;
		current->name = get_name(envp[i]);
		current->value = get_value(envp[i]);
		current->displayed = 0;
		env = current;
		i++;
	}
	env->next =NULL;
	return (head);
}
