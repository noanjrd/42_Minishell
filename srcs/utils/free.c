/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:39:25 by njard             #+#    #+#             */
/*   Updated: 2025/05/12 14:27:16 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_token(t_token *token)
{
	t_token *temp;

	temp = token;
	while(temp)
	{
		temp = token->next;
		free(token->value);
		// free(token->type);
		free(token);
		token = temp;
	}
	return ;
}

void free_cmd(t_cmd *cmd)
{
	t_cmd *temp;

	temp = cmd;
	while(temp)
	{
		temp = cmd->next;
		free(cmd->value);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		// free(cmd->type);
		cmd = temp;
	}
	return ;
}

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
	// free_token(data->tokens);
	free_cmd(data->commands);
	if (data->here_doc == 1)
	{
		close(data->fd_here_doc);
		unlink("temp");
	}
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
