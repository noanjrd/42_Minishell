/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:35:47 by njard             #+#    #+#             */
/*   Updated: 2025/06/05 15:04:06 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			g_exit_code_signal = 0;

void	init_data(t_data *data, t_env *env, char **envp)
{
	data->paths_system = NULL;
	data->exit_code = 0;
	data->commands = NULL;
	if (envp && envp[0] != NULL)
		data->envp = envp;
	else
		data->envp = NULL;
	data->env = env_init(env, envp);
	data->line = NULL;
	data->fd_here_doc = -99;
	g_exit_code_signal = 0;
	data->nb_of_commands = 0;
	data->error_alrdy_displayed = 0;
	if (data->env && envp && envp[0] != NULL)
		initalising_path(data);
}

static char	*get_name(char *envp)
{
	int		i;
	char	*name;

	i = 0;
	while (envp[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	i = 0;
	while (envp[i] != '=')
	{
		name[i] = envp[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char	*get_value(char *envp)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (envp[i] != '=')
		i++;
	while (envp[j])
		j++;
	value = malloc((j - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (envp[i])
		value[j++] = envp[i++];
	value[j] = '\0';
	return (value);
}

t_env	*env_init(t_env *env, char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	if (!envp || envp[0] == NULL)
		return (NULL);
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
	env->next = NULL;
	return (head);
}
