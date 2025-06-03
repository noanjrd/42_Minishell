/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/06/02 16:29:37 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
static void	ft_sigitn(int sig)
{
	if (sig == SIGINT)
	{
		write(1,"\n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		g_exit_code_signal = 130;
	}
	return ;
}

void ft_parents_second_part(t_cmd *cmd, t_cmd *cmd_temp)
{
	if (cmd->next && cmd->next->type != IN_OUT_FILENAME)
	{
		cmd->next->prev_fdpipe = malloc(2 * sizeof(int));
		cmd->next->prev_fdpipe[0] = cmd_temp->fdpipe[0];
		cmd->next->prev_fdpipe[1] = cmd_temp->fdpipe[1];
	}
	else
	{
		if (cmd_temp->fdpipe[0] != -1)
			close(cmd_temp->fdpipe[0]);
		if (cmd_temp->fdpipe[1] != -1)
			close(cmd_temp->fdpipe[1]);
	}
}
void ft_parents(t_data *data, t_cmd *cmd, t_cmd *cmd_temp)
{
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
	cmd_temp = cmd;
	while (cmd->next && cmd->next->type == IN_OUT_FILENAME
		&& cmd->next->end == 0 && cmd->next->redirect_in_before == 1)
		cmd = cmd->next;
	ft_parents_second_part(cmd, cmd_temp);

}

void	ft_execve(t_data *data, t_cmd *cmd)
{
	if (builtin_check(cmd) == 1 && cmd->fdout != -1)
	{
		go_to_right_builtin(data, cmd->index);
	}
	else
	{
		if (cmd->path == NULL && data->error_alrdy_displayed == 0)
		{
			data->exit_code = 127;
			if (data->error_alrdy_displayed == 0)
				printf_error_beginning(data, cmd, 3);
		}
		else if (cmd->fdin != -1 && cmd->fdout != -1)
		{
			execve(cmd->path, cmd->tab, data->envp);
			data->error_alrdy_displayed = 1;
		}
	}
}

void	excve_apply(t_data *data, t_cmd *cmd, t_cmd *cmd_temp)
{
	if (builtin_check(cmd) == 2)
	{
		// printf("lol\n");
		cmd->check_fdin = -1;
		return (go_to_right_builtin(data, cmd->index));
	}
	cmd->fdpipe[0] = -1;
	cmd->fdpipe[1] = -1;
	pipe(cmd->fdpipe);
	cmd->pid = fork();
	signal(SIGINT ,ft_sigitn);
	signal(SIGQUIT ,SIG_IGN);
	if (cmd->pid == 0 && builtin_check(cmd) != 2)
	{
		dup_cases(cmd);
		ft_execve(data, cmd);
		ft_error_fork(data);
	}
	ft_parents(data, cmd, cmd_temp);
	return ;
}
