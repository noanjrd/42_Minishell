/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/05/26 11:49:08 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_error(t_data *data, t_cmd *cmd)
{
	// int  i = 0;
	
	// free(cmd->value);
	// free(cmd->infile);
	// free(cmd->outfile);
	// if (cmd->fdpipe)
	// 	free(cmd->fdpipe);
	// if (cmd->prev_fdpipe)
	// 	free(cmd->prev_fdpipe);
	// if (cmd->path)
	// 	free(cmd->path);
	// if (cmd->fdin > 0)
	// 	close(cmd->fdin);
	// if (cmd->fdout > 0)
	// 	close(cmd->fdout);
	// if (cmd->tab)
	// {
	// 	while (cmd->tab[i])
	// 	{
	// 		free(cmd->tab[i]);
	// 		i++;
	// 	}
	// 	free(cmd->tab);
	// }
	// free(cmd);
	// exit(data->exit_code);
	return ;
}

void	excve_apply(t_data *data, t_cmd *cmd, t_cmd *cmd_temp)
{
	if (builtin_check(data, cmd->tab[0]) == 2)
	{
		// printf("builtin1\n");
		go_to_right_builtin(data, cmd, cmd->index);
		cmd->check_fdin = -1;
		return ;
	}
	cmd->fdpipe[0] = -1;
	cmd->fdpipe[1] = -1;
	pipe(cmd->fdpipe);
	cmd->pid = fork();
	// printf("la< %s\n", cmd->value);
	if (cmd->pid == 0 && builtin_check(data, cmd->tab[0]) != 2)
	{
		if (cmd->fdin != -99 && cmd->check_fdin == 1)
		{
			// printf("ya un fdin %s\n", cmd->value);
			dup2(cmd->fdin, STDIN_FILENO);
			// close(cmd->fdin);
		}
		else if (cmd->prev_fdpipe && cmd->prev_fdpipe[0] != -1)
		{
			// printf("prev pipe existant %s\n", cmd->value);
			dup2(cmd->prev_fdpipe[0], STDIN_FILENO);
		}
		if (cmd->path != NULL && cmd->fdout != -99 && cmd->check_fdout == 1)
		{
			// printf("ya un fdout\n");
			dup2(cmd->fdout, STDOUT_FILENO);
		}
		else if (cmd->path != NULL && cmd->next && cmd->next->end == 0)
		{
			// printf("normal %s\n", cmd->value);
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
			// free(cmd->prev_fdpipe);
		}
		if (builtin_check(data, cmd->tab[0]) == 1 && cmd->fdout != -1)
		{
			// printf("builtin %s\n", cmd->value);
			// printf("%d\n", data->exit_code);
			go_to_right_builtin(data, cmd, cmd->index);

		}
		else
		{
			if (cmd->path == NULL && data->error_alrdy_displayed == 0)
			{
				data->exit_code = 127;
				if (data->error_alrdy_displayed == 0)
					write(2," command not found\n",19);
				// else if (access(cmd->value, F_OK) == 0)
				// 	write(2," Is a directory\n",16);

				
				// printf("exit code : %d\n", data->exit_code);
			}
			else if (cmd->fdin != -1 && cmd->fdout != -1)
			{
				// printf("exec exec %s\n", cmd->value);
				execve(cmd->path, cmd->tab, data->envp);
				data->error_alrdy_displayed = 1;
			}
		}
		// free();
		exit(data->exit_code);
		// ft_error(data, cmd);
	}
	// printf("%d\n", data->exit_code);
	if (cmd->check_fdin == -1 || cmd->check_fdout == -1)
		data->exit_code = 1;
	if (cmd->prev_fdpipe)
	{
		if (cmd->prev_fdpipe[0] != -1)
			close(cmd->prev_fdpipe[0]);
		if (cmd->prev_fdpipe[1] != -1)
			close(cmd->prev_fdpipe[1]);
		free(cmd->prev_fdpipe);
		cmd->prev_fdpipe = NULL;
	}
	// if (cmd->fdin)
	// 	close(cmd->fdin);
	
	cmd_temp = cmd;
	// printf("temp : %s\n", cmd_temp->value);
	while (cmd->next && cmd->next->type == IN_OUT_FILENAME && cmd->next->end == 0 && cmd->next->redirect_in_before == 1)
	{
		// printf("loop\n");
		cmd = cmd->next;
	}
	// printf("### %s\n", cmd->value);
	if (cmd->next && cmd->next->type != IN_OUT_FILENAME)
	{
		// printf("prevvv %s, next %s\n",cmd_temp->value, cmd->next->value);
		cmd->next->prev_fdpipe = malloc(2 * sizeof(int));
		cmd->next->prev_fdpipe[0] = cmd_temp->fdpipe[0];
		cmd->next->prev_fdpipe[1] = cmd_temp->fdpipe[1];
		// if (cmd_temp->fdpipe[1] != -1)
		// 	close(cmd_temp->fdpipe[1]);
	}
	else
	{
		if (cmd_temp->fdpipe[0] != -1)
			close(cmd_temp->fdpipe[0]);
		if (cmd_temp->fdpipe[1] != -1)
			close(cmd_temp->fdpipe[1]);
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
	// while (cpy_cmd && cpy_cmd->type == IN_OUT_FILENAME)
	// {
	// 	cpy_cmd = cpy_cmd->next;
	// }
	while (cpy_cmd && j < data->nb_of_commands)
	{
		if (cpy_cmd->type !=IN_OUT_FILENAME)
		{
			// printf("wait %s\n", cpy_cmd->value);
			waitpid(cpy_cmd->pid, &status, 0); 
			if (((cpy_cmd->check_fdout != -1) && (cpy_cmd->check_fdin != -1)) && WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			j++;
		}
		if (cpy_cmd->red_out == 1)
			j++;
		cpy_cmd = cpy_cmd->next;
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
			// printf("crashing %s\n", cmd->value);
			fd = open(cmd->value, open(cmd->value,O_TRUNC, 0700));
			close(fd);
		}
	}
	else if (cmd->red_out == 0 && cmd->deleted == 0)
	{
		excve_apply(data, cmd, NULL);
	}
	return ;
}

void	ft_check_extra(t_data *data, t_cmd *cmd)
{
	int fd;
	if (cmd->first == 1 && cmd->next == NULL 
		&& (cmd->value[0] == '.' || cmd->value[0] == '/' ))
	{
		// printf("here\n");
		if (access(cmd->value, F_OK) == 0)
		{
			fd = open(cmd->value, O_RDONLY);
			if (fd < 0)
			{
				perror("Error");
			}
			else
				write(2, " Is a directory\n",16);
			close(fd);
			cmd->check_fdin = -1;
			data->exit_code = 126;
			// printf("%d\n", data->exit_code);
			return ;
		}
		else
		{
			data->exit_code = 127;
			cmd->check_fdin = -1;
			write(2, " No such file or directory\n",27);
			return ;
		}
	}
	check_fdout_between(data, cmd);
}

void	real_exec(t_data *data)
{
	t_cmd	*cpy_cmd;
	int i;

	cpy_cmd = data->commands;
	i = 0;
	// pipe(cpy_cmd->fdpipe);
	while (cpy_cmd && i < data->nb_of_commands)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME || cpy_cmd->red_out == 1)
		{
			// go_to_right_builtin(data, cpy_cmd->index);
			// excve_apply(data, cpy_cmd);
			ft_check_extra(data, cpy_cmd);
			i++;
		}
		// printf("here %s\n", cpy_cmd->value);
		cpy_cmd  = cpy_cmd->next;
	}
	wait_p(data);
	return ;
}
