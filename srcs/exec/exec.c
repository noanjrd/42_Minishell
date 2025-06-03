/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 12:27:57 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_error_beginning(t_data *data, t_cmd *cmd, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		cmd->check_fdin = -1;
		data->exit_code = 126;
	}
	if (error == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (error == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_error_fork(data);
	}
	return ;
}

void	check_middle_fdout(t_data *data, t_cmd *cmd)
{
	int	fd;

	if (cmd->red_out == 1 && cmd->outfile)
	{
		if (cmd->red_append == 0)
		{
			fd = open(cmd->value, open(cmd->value, O_TRUNC, 0700));
			close(fd);
		}
	}
	else if (cmd->red_out == 0 && cmd->deleted == 0)
	{
		excve_apply(data, cmd, NULL);
	}
	return ;
}

void	ft_check_folder_or_file(t_data *data, t_cmd *cmd)
{
	struct stat	sb;
	int			fd;

	stat(cmd->value, &sb);
	if (S_ISREG(sb.st_mode))
	{
		fd = open(cmd->value, O_RDONLY);
		if (fd < 0)
		{
			cmd->check_fdin = -1;
			data->exit_code = 126;
			perror("Error");
		}
		else
		{
			cmd->path = ft_copy(cmd->value);
			check_middle_fdout(data, cmd);
		}
		close (fd);
	}
	else
	{
		printf_error_beginning(data, cmd, 1);
	}
}

void	ft_check_folder_file(t_data *data, t_cmd *cmd)
{
	if (cmd->first == 1 && cmd->next == NULL
		&& (cmd->value[0] == '.' || cmd->value[0] == '/' ))
	{
		if (access(cmd->value, F_OK) == 0)
		{
			return (ft_check_folder_or_file(data, cmd));
		}
		else
		{
			data->exit_code = 127;
			cmd->check_fdin = -1;
			printf_error_beginning(data, cmd, 2);
			return ;
		}
	}
	check_middle_fdout(data, cmd);
}

void	exec(t_data *data)
{
	t_cmd	*cpy_cmd;
	int		i;

	cpy_cmd = data->commands;
	i = 0;
	while (cpy_cmd && i < data->nb_of_commands)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME || cpy_cmd->red_out == 1)
		{
			ft_check_folder_file(data, cpy_cmd);
			i++;
		}
		cpy_cmd = cpy_cmd->next;
	}
	wait_p(data);
	return ;
}
