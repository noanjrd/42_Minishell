/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:58:00 by naankour          #+#    #+#             */
/*   Updated: 2025/06/03 18:58:00 by naankour         ###   ########.fr       */
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

void	display_error_here_doc(t_cmd *cpy_cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cpy_cmd->value, 2);
	ft_putstr_fd(": ", 2);
	perror("");
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
				display_error_here_doc(cpy_cmd);
			}
			if (fd < 0)
				stop_all_out_before_and_after(data->commands, cpy_cmd);
			if (fd >= 0)
				close(fd);
		}
		cpy_cmd = cpy_cmd->next;
	}
}
