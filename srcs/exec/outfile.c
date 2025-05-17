/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:21 by njard             #+#    #+#             */
/*   Updated: 2025/05/17 16:18:08 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_relink_linked_list(t_token *token, t_cmd *cmd, char *value2, int i)
// {
// 	if (!token || !token->next || !token->next->next)
// 		return ;
// 	t_token *start;
// 	start = token;
// 	token = token->next;
// 	t_token *temp;
// 	while (i > 0 && token->next)
// 	{
// 		token = token->next;
// 		i--;
// 	}
// 	// printf("|%s|\n", token->value);
// 	while (token->next && ft_strcmp(token->next->value, value2) != 0)
// 	{
// 		temp = token->next;
// 		free(token->value);
// 		free(token);
// 		token = temp; 
// 	}
// 	start->next = token;
// 	if (token->next->next && (token->next->next->type == REDIRECT_APPEND || token->next->next->type == REDIRECT_OUT))
// 	{
// 		ft_relink_linked_list(start, cmd, value2, 1);
// 	}
// 	return ;
// }

// void	ft_relink_linked_cmd(t_cmd *cmd, char *value2, int i)
// {
// 	t_cmd *temp;
// 	t_cmd *start;
// 	start = cmd;
// 	cmd = cmd->next;
// 	while (i > 0)
// 	{
// 		if (cmd->next)
// 			cmd = cmd->next;
// 		i--;
// 	}
// 	while (cmd && cmd->type == IN_OUT_FILENAME && ft_strcmp(cmd->value, value2) != 0)
// 	{
// 		temp = cmd->next;
// 		free(cmd->value);
// 		free(cmd->infile);
// 		free(cmd->outfile);
// 		free(cmd);
// 		cmd = temp; 
// 	}
// 	start->next = cmd;
// 	if (cmd->next && cmd->next->type == IN_OUT_FILENAME)
// 	{
// 		ft_relink_linked_cmd(start, value2, 1);
// 	}
// 	return ;
// }

// void	open_fdout(t_data *data, t_token *token, t_cmd *cmd)
// {
// 	t_token *cpy;
// 	int fdout;
// 	int check;
// 	int	append;

// 	check = 0;
// 	cpy = token->next;
// 	while (cpy)
// 	{
// 		if (!cpy->next->next && check == 0)
// 		{
// 			if (cpy->type == REDIRECT_APPEND)
// 			{
// 				cmd->red_append = 1;
// 				fdout = open(cpy->next->value, O_WRONLY | O_CREAT | O_APPEND , 0700);
// 			}
// 			else
// 				fdout = open(cpy->next->value, O_WRONLY | O_CREAT | O_TRUNC , 0700);
// 			if (fdout < 0)
// 			{
// 				data->exit_code = 1;
// 				perror("Error");
// 				cmd->check_fdout = 0;
// 			}
// 			else
// 				cmd->check_fdout = 1;
// 			free(cmd->outfile);
// 			cmd->outfile = ft_copy(cpy->next->value);
// 			cmd->fdout = fdout;
// 			return ;
// 		}
// 		if (cpy->next->next && (cpy->next->next->type == REDIRECT_OUT || cpy->next->next->type == REDIRECT_APPEND))
// 		{
// 			if (cpy->next->next->type == REDIRECT_OUT)
// 				append = 0;
// 			if (cpy->next->next->type == REDIRECT_APPEND)
// 				append = 1;
// 			cpy = cpy->next->next;
// 			check = 1;
// 		}
// 		else 
// 			break;
// 	}
// 	if (append == 1)
// 	{
// 		printf("app\n");
// 		cmd->red_append = 1;
// 		fdout = open(cpy->next->value,O_WRONLY | O_CREAT | O_APPEND, 0700);
// 		cmd->check_fdout = 1;
// 	}
// 	else 
// 	{
// 		fdout = open(cpy->next->value,O_WRONLY | O_CREAT, 0700);
// 		cmd->check_fdout = 1;
// 	}
// 	if (fdout < 0)
// 	{
// 		data->exit_code = 1;
// 		// perror("Error");
// 		cmd->check_fdout = 0;
// 	}
// 	free(cmd->outfile);
// 	cmd->outfile = ft_copy(cpy->next->value);
// 	cmd->fdout = fdout;
// 	return ;
// }

void	reach_furthest_fd(t_cmd *cmd, t_token *token)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_token = token;
	cpy_cmd = cmd;
	while (cpy_cmd && (cpy_cmd->outfile || (cpy_cmd->next && cpy_cmd->next->redirect_in_before == 1)))
	{
		cpy_cmd = cpy_cmd->next;
	}
	// printf(",,,,,%s\n", cpy_cmd->value);
	if (cpy_cmd->red_append == 1)
		cmd->fdout = open(cpy_cmd->value,O_WRONLY | O_CREAT | O_APPEND, 0700);
	if (cpy_cmd->red_append == 0)
		cmd->fdout = open(cpy_cmd->value,O_WRONLY | O_CREAT, 0700);
	if (cmd->fdout > 0)
		cmd->check_fdout = 1;
	free(cmd->outfile);
	cmd->outfile = ft_copy(cpy_cmd->value);
	printf("cmd_out reach furthest: %s\n", cmd->outfile);
	printf("cmd_value reach furthest: %s\n", cmd->value);
	printf("copy_value reach furthest: %s\n", cpy_cmd->value);
	// cmd = cmd->next;
	// token = token->next;
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
			printf("ddddoutcmd: %s\n", cpy_cmd->value);
			if (cpy_cmd->type == WORD )
			{
				reach_furthest_fd(cpy_cmd, cpy_token);
				printf("outcmd: %s\n", cpy_cmd->value);
				cpy_cmd = cpy_cmd->next;
				cpy_token = cpy_token->next;
				continue;
			}
			if (cpy_cmd->next->red_append == 1)
				cpy_cmd->fdout = open(cpy_cmd->value,O_WRONLY | O_CREAT | O_APPEND, 0700);
			if (cpy_cmd->next->red_append == 0)
				cpy_cmd->fdout = open(cpy_cmd->value,O_WRONLY | O_CREAT, 0700);
			if (cpy_cmd->fdout > 0)
				cpy_cmd->check_fdout = 1;
		}
		if (cpy_cmd->next && ft_check_type(cpy_token) == 1)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	return ;
}
