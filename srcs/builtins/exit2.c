/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:17:32 by naankour          #+#    #+#             */
/*   Updated: 2025/06/02 17:17:32 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_before_exit(t_data *data)
{
	int	i;

	i = 0;
	clear_history();
	if (data->tokens)
	{
		free_token_list(data->tokens);
		data->tokens = NULL;
	}
	free_cmd(data->commands);
	if (data->env)
	{
		free_env(data->env);
		data->env = NULL;
	}
	// ft_free_tab
	if (data->paths_system)
	{
		while (data->paths_system[i])
		{
			free(data->paths_system[i]);
			i++;
		}
		free(data->paths_system);
	}
	free(data);
}

void	free_and_exit(t_data *data, int exit_code)
{
	free_before_exit(data);
	exit(exit_code);
}
