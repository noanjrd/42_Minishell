/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:18:56 by njard             #+#    #+#             */
/*   Updated: 2025/05/19 14:00:45 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_error(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;
	int fd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	while (cpy_cmd)
	{
		if (cpy_cmd->type == IN_OUT_FILENAME)
		{
			fd = open(cpy_cmd->value, O_RDONLY);
			// printf("@@@@@ %s\n", cpy_cmd->value);
			if (fd < 0)
			{
				cpy_cmd->check_fdin = -1;
				cpy_cmd->check_fdout = -1;
			}
			if (fd < 0 && data->error_alrdy_displayed == 0)
			{
				data->exit_code = 1;
				data->error_alrdy_displayed = 1;
				
				// printf("error here %d %s\n", data->exit_code, cpy_cmd->value);
				perror("Error");
			}
			close(fd);
		}
		cpy_cmd = cpy_cmd->next;
	}
	return ;
}

void fdin_before(t_data *data, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	if (cmd->fdin > 0)
		return ;
	// printf("BEFOOOORE %s\n", cmd->value);
	if (cmd->next->redirect_in_before == 0)
		return ;
	while (cpy_cmd && cpy_cmd->next && cpy_cmd->next->type == IN_OUT_FILENAME && cpy_cmd->next->red_out == 0)
	{
		cpy_cmd = cpy_cmd->next;
	}
	// printf("+++++%s\n", cpy_cmd->value);
	// cmd->outfile = ft_copy(cpy_cmd->outfile);
	// cmd->fdout = cpy_cmd->fdout;
	if (cmd->fdout > 0)
		cmd->check_fdout = 1;
	if (cpy_cmd->here_doc == 1)
	{
		cmd->fdin = data->fd_here_doc;
		cmd->check_fdin = 1;
	}
	else
	{
		free(cmd->infile);
		cmd->infile = ft_copy(cpy_cmd->value);
		cmd->fdin = open(cpy_cmd->value ,O_RDONLY, 0700);
		if (cmd->fdin > 0)
				cmd->check_fdin = 1;
	}
	return ;
}

void fdin_after(t_data *data, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	// printf("AFTRRRRR %s\n", cmd->value);
	if (cmd->next && cmd->next->type == WORD && cmd->type == IN_OUT_FILENAME && cmd->next->infile)
	{
		if (cmd->here_doc == 1)
		{
			cmd->next->fdin = data->fd_here_doc;
			cmd->next->check_fdin = 1;
		}
		else
		{
			cpy_cmd->next->fdin = open(cpy_cmd->next->infile ,O_RDONLY, 0700);
			if (cpy_cmd->next->fdin > 0)
				cpy_cmd->next->check_fdin = 1;
		}
	}
	return ;
}
