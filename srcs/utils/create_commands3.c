/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:37:48 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 11:33:16 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rest_ofthesteps_five(t_cmd *cmd)
{
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	while (cpy_cmd)
	{
		if (!cpy_cmd->next && cpy_cmd->type == IN_OUT_FILENAME)
			cpy_cmd->end = 1;
		cpy_cmd = cpy_cmd->next;
	}
	return ;
}

void	rest_ofthesteps_four(t_cmd *cmd, int check)
{
	t_cmd	*cpy_cmd;
	t_cmd	*temp;

	cpy_cmd = cmd;
	while (cpy_cmd)
	{
		if (cpy_cmd->redirect_in_before == 1)
		{
			check = 0;
			temp = cpy_cmd;
			while (temp)
			{
				if (temp->redirect_in_before == 0)
				{
					check = 1;
					break ;
				}
				temp = temp->next;
			}
			if (check == 0)
				cpy_cmd->end = 1;
		}
		cpy_cmd = cpy_cmd->next;
	}
	rest_ofthesteps_five(cmd);
}
