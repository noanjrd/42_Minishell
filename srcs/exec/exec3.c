/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 15:17:08 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_error_fork(t_data *data)
{
	int exitc;

	exitc = data->exit_code;
	if (data->tokens)
	{
		free_token_list(data->tokens);
		data->tokens = NULL;
	}
	free_cmd(data->commands);
	free_data(data);
	exit(exitc);
	return ;
}

void dup_cases(t_cmd *cmd)
{
	if (cmd->fdin != -99 && cmd->check_fdin == 1)
		dup2(cmd->fdin, STDIN_FILENO);
	else if (cmd->prev_fdpipe && cmd->prev_fdpipe[0] != -1)
		dup2(cmd->prev_fdpipe[0], STDIN_FILENO);
	if (cmd->path != NULL && cmd->fdout != -99 && cmd->check_fdout == 1)
		dup2(cmd->fdout, STDOUT_FILENO);
	else if ((cmd->path != NULL || ft_strcmp(cmd->value,"export") == 0) 
		&& cmd->next && cmd->next->end == 0)
		dup2(cmd->fdpipe[1], STDOUT_FILENO);
	if (cmd->fdpipe[0] != -1)
		close(cmd->fdpipe[0]);
	if (cmd->fdpipe[1] != -1)
		close(cmd->fdpipe[1]);
	if (cmd->prev_fdpipe)
	{
		if (cmd->prev_fdpipe[0] != -1)
			close(cmd->prev_fdpipe[0]);
		if (cmd->prev_fdpipe[1] != -1)
			close(cmd->prev_fdpipe[1]);
	}
	return ;
}

void wait_p(t_data *data)
{
	t_cmd *cpy_cmd;
	int j;
	int status;

	cpy_cmd = data->commands;
	j = 0;
	while (cpy_cmd && j < data->nb_of_commands)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME)
		{
			waitpid(cpy_cmd->pid, &status, 0);
			if (((cpy_cmd->check_fdout != -1) 
			&& (cpy_cmd->check_fdin != -1)) && WIFEXITED(status))
			{
				data->exit_code = WEXITSTATUS(status);
			}
			j++;
		}
		if (cpy_cmd->red_out == 1)
			j++;
		cpy_cmd = cpy_cmd->next;
	}
	return ;
}
