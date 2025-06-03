/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:18:56 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 12:44:21 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stop_all_out_before_and_after(t_cmd *cmd, t_cmd *target)
{
	int		fd;
	t_cmd	*cpy_cmd;

	(void)fd;
	cpy_cmd = cmd;
	target->check_fdin = -1;
	target->check_fdout = -1;
	while (cpy_cmd->index != target->index)
	{
		cpy_cmd->fdout = -1;
		cpy_cmd->check_fdout = -1;
		cpy_cmd = cpy_cmd->next;
		if (cpy_cmd->red_append == 0 && cpy_cmd->check_fdout != -1)
			fd = open(cpy_cmd->value, O_TRUNC, 0700);
	}
	cpy_cmd = target;
	while (cpy_cmd && cpy_cmd->red_out == 1)
	{
		cpy_cmd->check_fdout = -1;
		cpy_cmd = cpy_cmd->next;
	}
	return ;
}

void	fd_error(t_data *data, int fd)
{
	t_cmd	*cpy_cmd;

	cpy_cmd = data->commands;
	while (cpy_cmd)
	{
		if (cpy_cmd->type == IN_OUT_FILENAME
			&& cpy_cmd->here_doc == 0)
		{
			if (cpy_cmd->red_out == 0)
				fd = open(cpy_cmd->value, O_RDONLY);
			else if (data->error_alrdy_displayed == 0)
				fd = open(cpy_cmd->value, O_WRONLY | O_CREAT, 0700);
			if (fd < 0 && data->error_alrdy_displayed == 0)
			{
				data->exit_code = 1;
				data->error_alrdy_displayed = 1;
				perror("Error");
			}
			if (fd < 0)
				stop_all_out_before_and_after(data->commands, cpy_cmd);
			if (fd >= 0)
				close(fd);
		}
		cpy_cmd = cpy_cmd->next;
	}
}

void	fdin_before_next(t_cmd *cmd, t_cmd *cpy_cmd)
{
	if (ft_strcmp(cmd->value, cpy_cmd->value) != 0)
	{
		free(cmd->infile);
		cmd->infile = ft_copy(cpy_cmd->value);
		cmd->fdin = open(cpy_cmd->value, O_RDONLY, 0700);
	}
	else
		cmd->fdin = open(cmd->infile, O_RDONLY, 0700);
	if (cmd->fdin > 0)
		cmd->check_fdin = 1;
	return ;
}

void	fdin_before(t_data *data, t_cmd *cmd)
{
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	if (cmd->next->redirect_in_before == 0)
		return ;
	while (cpy_cmd && cpy_cmd->next
		&& cpy_cmd->next->type == IN_OUT_FILENAME
		&& cpy_cmd->next->red_out == 0)
		cpy_cmd = cpy_cmd->next;
	if (cmd->fdout > 0)
		cmd->check_fdout = 1;
	if (cpy_cmd->here_doc == 1)
	{
		cmd->fdin = data->fd_here_doc;
		cmd->check_fdin = 1;
	}
	else
	{
		fdin_before_next(cmd, cpy_cmd);
	}
}

void	fdin_after(t_data *data, t_cmd *cmd)
{
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	if (cmd->next && cmd->next->type == WORD
		&& cmd->type == IN_OUT_FILENAME && cmd->next->infile)
	{
		if (cmd->here_doc == 1)
		{
			cmd->next->fdin = data->fd_here_doc;
			cmd->next->check_fdin = 1;
		}
		else
		{
			cpy_cmd->next->fdin = open(cpy_cmd->next->infile, O_RDONLY, 0700);
			if (cpy_cmd->next->fdin > 0)
				cpy_cmd->next->check_fdin = 1;
		}
	}
	return ;
}
