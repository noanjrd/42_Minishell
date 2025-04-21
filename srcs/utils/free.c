/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:39:25 by njard             #+#    #+#             */
/*   Updated: 2025/04/21 15:23:43 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function frees the memory allocated for data.
void free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->paths_system)
	{
		while (data->paths_system[i])
		{
			free(data->paths_system[i]);
			i++;
		}
		free(data->paths_system);
	}
	free(data->line);
	free_env(data->env);
	clear_history();
	free(data);
	return ;
}

// This function frees the memory allocated for the environment.
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
