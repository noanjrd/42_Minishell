/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/05/12 15:32:46 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	excve_apply(t_data *data, t_cmd *cmd)
{
	pipe(cmd->fdpipe);
	printf("la< %s\n", cmd->value);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->fdin != -99 && cmd->check_fdin == 1)
			dup2(cmd->fdin, STDIN_FILENO);
		else if (cmd->prev_fdpipe)
		{
			printf("prev pipe existant\n");
			dup2(cmd->prev_fdpipe[0], STDIN_FILENO);
		}
		if (cmd->fdout != -99 && cmd->check_fdout == 1)
			dup2(cmd->fdout, STDOUT_FILENO);
		else if (cmd->next)
			dup2(cmd->fdpipe[1], STDOUT_FILENO);
		close(cmd->fdpipe[0]);
		close(cmd->fdpipe[1]);
		if (cmd->prev_fdpipe) // Ferme les descripteurs de pipe précédent
		{
			close(cmd->prev_fdpipe[0]);
			close(cmd->prev_fdpipe[1]);
		}
		if (builtin_check(data, cmd->tab[0]) == 1)
			go_to_right_builtin(data, cmd->index);
		else
			execve(cmd->path, cmd->tab, data->envp);
		perror("execve");
		exit(data->exit_code);
	}
	if (cmd->prev_fdpipe)
	{
		close(cmd->prev_fdpipe[0]);
		close(cmd->prev_fdpipe[1]);
		free(cmd->prev_fdpipe);
		cmd->prev_fdpipe = NULL;
	}
	if (cmd->next && cmd->next->type != IN_OUT_FILENAME)
	{
		cmd->next->prev_fdpipe = malloc(2 * sizeof(int));
		cmd->next->prev_fdpipe[0] = cmd->fdpipe[0];
		cmd->next->prev_fdpipe[1] = cmd->fdpipe[1];
	}
	else
	{
		close(cmd->fdpipe[0]);
		close(cmd->fdpipe[1]);
	}

	// close(cmd->prev_fdpipe[0]);
	// close(cmd->prev_fdpipe[1]);

	return ;
}

void wait_p(t_data *data)
{
	t_cmd *cpy_cmd;
	int j;
	int status;

	cpy_cmd = data->commands;
	while (cpy_cmd && cpy_cmd->type == IN_OUT_FILENAME)
	{
		cpy_cmd = cpy_cmd->next;
	}
	while (j < data->nb_of_commands)
	{
		if (cpy_cmd->pid > 0 && cpy_cmd->fdin != -1)
		{
			waitpid(cpy_cmd->pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		cpy_cmd = cpy_cmd->next;
		j++;
	}
}

void	check_if_builtin(t_data *data, t_cmd *cmd, char *s)
{
	// if (builtin_check(data, s) == 1)
	// {
	// 	pipe(cmd->fdpipe);
	// 	cmd->pid = fork();
	// 	if (cmd->pid == 0)
	// 	{
	// 		if (cmd->fdout != -99 && cmd->check_fdout == 1)
	// 			dup2(cmd->fdout, STDOUT_FILENO);
	// 		else if (cmd->next)
	// 			dup2(cmd->fdpipe[1], STDOUT_FILENO);
	// 		close(cmd->fdpipe[0]);
	// 		close(cmd->fdpipe[1]);
	// 		// execve(cmd->path, cmd->tab, data->envp);
	// 		go_to_right_builtin(data, cmd->index);
	// 	}
	// 	if (cmd->prev_fdpipe)
	// 	{
	// 		close(cmd->prev_fdpipe[0]);
	// 		close(cmd->prev_fdpipe[1]);
	// 		free(cmd->prev_fdpipe);
	// 		cmd->prev_fdpipe = NULL;
	// 	}
	// 	if (cmd->next && cmd->next->type != IN_OUT_FILENAME)
	// 	{
	// 		cmd->next->prev_fdpipe = malloc(3 * sizeof(int));
	// 		cmd->next->prev_fdpipe[0] = cmd->fdpipe[0];
	// 		cmd->next->prev_fdpipe[1] = cmd->fdpipe[1];
	// 	}
	// 	else
	// 	{
	// 		close(cmd->fdpipe[0]);
	// 		close(cmd->fdpipe[1]);
	// 	}
	// 	printf("builtin\n");
	// }
	excve_apply(data, cmd);
	return ;
}

void	real_exec(t_data *data)
{
	t_cmd	*cpy_cmd;
	int i;

	cpy_cmd = data->commands;
	i = 0;
	while (cpy_cmd && cpy_cmd->type == IN_OUT_FILENAME)
	{
		cpy_cmd = cpy_cmd->next;
	}
	pipe(cpy_cmd->fdpipe);
	while (i < data->nb_of_commands)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME)
		{
			excve_apply(data, cpy_cmd);
			i++;
		}
		printf("here\n");
		cpy_cmd  = cpy_cmd->next;
	}
	wait_p(data);
	return ;
}
