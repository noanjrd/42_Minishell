/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:21 by njard             #+#    #+#             */
/*   Updated: 2025/04/30 14:02:03 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_relink_linked_list(t_token *token, t_cmd *cmd, char *value2, int i)
{
	if (!token || !token->next || !token->next->next)
		return ;
	t_token *start;
	start = token;
	token = token->next;
	t_token *temp;
	while (i > 0 && token->next)
	{
		token = token->next;
		i--;
	}
	// printf("|%s|\n", token->value);
	while (token->next && ft_strcmp(token->next->value, value2) != 0)
	{
		temp = token->next;
		free(token->value);
		free(token);
		token = temp; 
	}
	start->next = token;
	if (token->next->next)
	{
		ft_relink_linked_list(start, cmd, value2, 1);
	}
	return ;
}

void	ft_relink_linked_cmd(t_cmd *cmd, char *value2, int i)
{
	t_cmd *temp;
	t_cmd *start;
	start = cmd;
	cmd = cmd->next;
	while (i > 0)
	{
		if (cmd->next)
			cmd = cmd->next;
		i--;
	}
	while (cmd && cmd->type == IN_OUT_FILENAME && ft_strcmp(cmd->value, value2) != 0)
	{
		temp = cmd->next;
		free(cmd->value);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = temp; 
	}
	start->next = cmd;
	if (cmd->next && cmd->next->type == IN_OUT_FILENAME)
		ft_relink_linked_cmd(start, value2, 1);
	return ;
}

void	open_fdout(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token *cpy;
	int fdout;
	int check;

	check = 0;

	cpy = token;
	cpy = cpy->next;
	// printf("%s", cpy->value);
	while (cpy)
	{
		if (!cpy->next->next && check == 0)
		{
			// printf("mdr\n");
			fdout = open(cpy->next->value,O_WRONLY | O_CREAT , 0644);
			if (fdout < 0)
            {
				data->exit_code = 1;
				cmd->check_open = -1;
            }
			cmd->outfile = cpy->next->value;
			cmd->fdout = fdout;
			return ;
		}
		if (cpy->next->next && (cpy->next->next->type == REDIRECT_OUT || cpy->next->next->type == REDIRECT_APPEND))
		{
			cpy = cpy->next->next;
			check = 1;
		}
		else 
			break;
	}
	fdout = open(cpy->next->value,O_WRONLY | O_CREAT , 0644 );
	cmd->outfile = cpy->next->value;
	cmd->fdout = fdout;
	// printf("lol\n");
	ft_relink_linked_list(token,cmd, cpy->next->value,0);
	// printf("%s\n", cpy->next->value);
	ft_relink_linked_cmd(cmd, cpy->next->value, 0);
	// ft_modify_command_fdout(data, token->value,  fdout, cpy->next->value);
	// data->fdin[data->fdin_index] = open(token->value, O_WRONLY | O_CREAT , 0644);
	// if (data->fdin[data->fdin_index] < 0)
	// {
	// 	printf("error");
	// }
	return ;
}
