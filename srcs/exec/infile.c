/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:18:56 by njard             #+#    #+#             */
/*   Updated: 2025/05/16 15:09:00 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void fdin_before(t_data *data, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	if (cmd->fdin > 0)
		return ;
	printf("BEFOOOORE\n");
	if (cmd->next->redirect_in_before == 0)
		return ;
	while (cpy_cmd && cpy_cmd->next && cpy_cmd->next->type == IN_OUT_FILENAME && cpy_cmd->next->red_out == 0)
	{
		cpy_cmd = cpy_cmd->next;
	}
	// printf("+++++%s\n", cpy_cmd->value);
	cmd->outfile = ft_copy(cpy_cmd->outfile);
	cmd->fdout = cpy_cmd->fdout;
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
		else
		{
			perror("Error");
			data->exit_code = 1;
		}
	}
	return ;
}

void fdin_after(t_data *data, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	printf("AFTRRRRR %s\n", cmd->value);
	if (cmd->next && cmd->next->type == WORD && cmd->type != IN_OUT_FILENAME)
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
			else
			{
				perror("Error");
				data->exit_code = 1;
			}
		}
	}
	return ;
}

void	fdin_check(t_data *data, t_cmd *cpy_cmd)
{
	if (cpy_cmd->here_doc == 0)
	{
		cpy_cmd->fdin = open(cpy_cmd->infile,O_RDONLY, 0700);
		if (cpy_cmd->fdin >= 0)
			cpy_cmd->check_fdin = 1;
		else
		{
			printf("faux fdin\n");
			data->exit_code = 1;
		}
	}
	else
	{
		cpy_cmd->fdin = data->fd_here_doc;
		cpy_cmd->check_fdin = 1;
	}
	return ;
}
