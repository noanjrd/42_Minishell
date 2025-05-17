/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/05/17 16:18:54 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	excve_apply(t_data *data, t_cmd *cmd)
{
	if (builtin_check(data, cmd->tab[0]) == 2)
	{
		printf("builtin1\n");
		go_to_right_builtin(data, cmd->index);
		return ;
	}
	cmd->fdpipe[0] = -1;
	cmd->fdpipe[1] = -1;
	pipe(cmd->fdpipe);
	cmd->pid = fork();
	printf("la< %s\n", cmd->value);
	if (cmd->pid == 0 && builtin_check(data, cmd->tab[0]) != 2)
	{
		if (cmd->fdin != -99 && cmd->check_fdin == 1)
		{
			printf("icii\n");
			dup2(cmd->fdin, STDIN_FILENO);
		}
		else if (cmd->prev_fdpipe && cmd->prev_fdpipe[0] != -1)
		{
			printf("prev pipe existant %s\n", cmd->value);
			dup2(cmd->prev_fdpipe[0], STDIN_FILENO);
		}
		if (cmd->path != NULL && cmd->fdout != -99 && cmd->check_fdout == 1)
		{
			printf("ya un fdout\n");
			dup2(cmd->fdout, STDOUT_FILENO);
		}
		else if (cmd->path != NULL && cmd->next && cmd->next->end == 0)
		{
			printf("normal %s\n", cmd->value);
			dup2(cmd->fdpipe[1], STDOUT_FILENO);
		}
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

		if (builtin_check(data, cmd->tab[0]) == 1)
		{
			printf("builtin\n");
			go_to_right_builtin(data, cmd->index);
		}
		else
		{
			if (cmd->path == NULL)
			{
				data->exit_code = 127;
				if (access(cmd->value, F_OK) == 0)
					write(2,"Is a directory\n",15);
				else if (data->error_alrdy_displayed == 0)
					write(2,"command not found\n",18);
			}
			else if (cmd->fdin != -1)
			{
				printf("exec exec\n");
				execve(cmd->path, cmd->tab, data->envp);
			}
		}
		exit(data->exit_code);
	}
	if (cmd->prev_fdpipe)
	{
		if (cmd->prev_fdpipe[0] != -1)
			close(cmd->prev_fdpipe[0]);
		if (cmd->prev_fdpipe[1] != -1)
			close(cmd->prev_fdpipe[1]);
		free(cmd->prev_fdpipe);
		cmd->prev_fdpipe = NULL;
	}
	while (cmd->next && cmd->next->type == IN_OUT_FILENAME && cmd->next->redirect_in_before == 1)
	{
		printf("loop\n");
		cmd = cmd->next;
	}
	printf("### %s\n", cmd->value);
	if (cmd->next && cmd->next->type != IN_OUT_FILENAME)
	{
		printf("prevvv %s\n", cmd->next->value);
		cmd->next->prev_fdpipe = malloc(2 * sizeof(int));
		cmd->next->prev_fdpipe[0] = cmd->fdpipe[0];
		cmd->next->prev_fdpipe[1] = cmd->fdpipe[1];
		if (cmd->fdpipe[1] != -1)
			close(cmd->fdpipe[1]);
	}
	else
	{
		if (cmd->fdpipe[0] != -1)
			close(cmd->fdpipe[0]);
		if (cmd->fdpipe[1] != -1)
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
	j = 0;
	while (cpy_cmd && cpy_cmd->type == IN_OUT_FILENAME)
	{
		cpy_cmd = cpy_cmd->next;
	}
	while (j < data->nb_of_commands)
	{
		if (cpy_cmd->pid > 0 && cpy_cmd->fdin >= 0)
		{
			waitpid(cpy_cmd->pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		cpy_cmd = cpy_cmd->next;
		j++;
	}
	return ;
}

void	check_fdout_between(t_data *data, t_cmd *cmd)
{
	int fd;

	if (cmd->red_out == 1 && cmd->outfile)
	{
		if (cmd->red_append == 0)
		{
			printf("crashing %s\n", cmd->value);
			fd = open(cmd->value, open(cmd->value,O_TRUNC, 0700));
			write(fd, "", 0);
			close(fd);
		}
	}
	else if (cmd->red_out == 0)
	{
		excve_apply(data, cmd);
	}
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
	// pipe(cpy_cmd->fdpipe);
	while (cpy_cmd && i < data->nb_of_commands)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME || cpy_cmd->red_out == 1)
		{
			// go_to_right_builtin(data, cpy_cmd->index);
			// excve_apply(data, cpy_cmd);
			check_fdout_between(data, cpy_cmd);
			i++;
		}
		// printf("here\n");
		cpy_cmd  = cpy_cmd->next;
	}
	wait_p(data);
	return ;
}
