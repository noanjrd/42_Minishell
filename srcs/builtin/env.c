/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:42:03 by njard             #+#    #+#             */
/*   Updated: 2025/03/27 11:42:54 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env *temp;

	temp = env;
	while(temp)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
	return ;
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
	i++;
	while (envp[i])
	{
		current = malloc(sizeof(t_env));
		env->next = current;
		current->name = get_name(envp[i]);
		current->value = get_value(envp[i]);
		env = current;
		i++;
	}
	env->next =NULL;
	return (head);
}
