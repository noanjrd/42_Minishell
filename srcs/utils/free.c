/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:39:25 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 11:25:47 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		temp = token->next;
		free(token->value);
		free(token);
		token = temp;
	}
	return ;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		temp = cmd->next;
		free(cmd->value);
		free(cmd->infile);
		free(cmd->outfile);
		if (cmd->fdpipe)
			free(cmd->fdpipe);
		if (cmd->prev_fdpipe)
			free(cmd->prev_fdpipe);
		if (cmd->path)
			free(cmd->path);
		if (cmd->fdin > 0)
			close(cmd->fdin);
		if (cmd->fdout > 0)
			close(cmd->fdout);
		if (cmd->tab)
			ft_free_tab(cmd->tab);
		free(cmd);
		cmd = temp;
	}
}

// This function frees the memory allocated for data.
void	free_data(t_data *data)
{
	int	i;

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
	if (data->env)
		free_env(data->env);
	if (data->fd_here_doc > 0)
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
	t_env	*temp;

	temp = env;
	while (temp)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
	env = NULL;
	return ;
}
