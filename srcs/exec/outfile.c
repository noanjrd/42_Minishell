/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:21 by njard             #+#    #+#             */
/*   Updated: 2025/05/25 10:25:22 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reach_furthest_fd(t_cmd *cmd, t_token *token)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_token = token;
	cpy_cmd = cmd;
	// printf("!!!!!%s\n", cmd->value);
	while ((cpy_cmd->next && cpy_cmd->next->next && cpy_cmd->next->deleted == 1 )||  cpy_cmd && cpy_cmd->check_fdin != -1 
		&& cpy_cmd->check_fdout != -1 && (cpy_cmd->outfile 
		|| (cpy_cmd->next && cpy_cmd->next->redirect_in_before == 1)))
	{
		cpy_cmd = cpy_cmd->next;
	}
	// printf(",,,,,%s\n", cpy_cmd->value);
	if (cpy_cmd->red_out == 1 && cpy_cmd->check_fdout >= 0)
	{
		if (cpy_cmd->red_append == 1)
			cmd->fdout = open(cpy_cmd->value,O_WRONLY | O_CREAT | O_APPEND, 0700);
		if (cpy_cmd->red_append == 0)
			cmd->fdout = open(cpy_cmd->value,O_WRONLY | O_CREAT, 0700);
		if (cmd->fdout > 0)
			cmd->check_fdout = 1;
		free(cmd->outfile);
		cmd->outfile = ft_copy(cpy_cmd->value);
	}
	return ;
}

void	open_fdout(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_token = token;
	cpy_cmd = cmd;
	while (cpy_token)
	{
		if (cpy_cmd->outfile && cpy_cmd->redirect_in_before == 0 || (cpy_cmd->next && cpy_cmd->next->redirect_in_before == 1))
		{
			// printf("ddddoutcmd: %s\n", cpy_cmd->value);
			if (cpy_cmd->type == WORD )
			{
				// printf("outcmd: %s\n", cpy_cmd->value);
				reach_furthest_fd(cpy_cmd, cpy_token);
				cpy_cmd = cpy_cmd->next;
				cpy_token = cpy_token->next;
				continue;
			}
		}
		if (cpy_cmd->next && ft_check_type(cpy_token) == 1)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	return ;
}
