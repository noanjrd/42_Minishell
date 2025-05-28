/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:37:48 by njard             #+#    #+#             */
/*   Updated: 2025/05/28 14:41:07 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rest_ofthesteps_five(t_cmd *cmd)
{
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	while (cpy_cmd)
	{
		// if (cpy_cmd->next && cpy_cmd->redirect_in_before == 1 && cpy_cmd->next->infile)
		// 	cpy_cmd->end = 1;
		if (!cpy_cmd->next && cpy_cmd->type == IN_OUT_FILENAME)
			cpy_cmd->end = 1;
		cpy_cmd = cpy_cmd->next;
	}
	return ;
}

void	rest_ofthesteps_four(t_cmd *cmd, int check)
{
	t_cmd	*cpy_cmd;
	t_cmd *temp;

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
					break;
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

void	rest_ofthesteps_three(t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		if (cpy_cmd && cpy_token->next && cpy_token->next->next && cpy_cmd->type != IN_OUT_FILENAME 
			&& (cpy_token->next->type == REDIRECT_IN || cpy_token->next->type == HERE_DOC || cpy_token->next->type == REDIRECT_OUT || cpy_token->next->type == REDIRECT_APPEND))
		{
			cpy_cmd->next->redirect_in_before = 1;
			cpy_cmd->infile = ft_copy(cpy_token->next->next->value);
			// printf("$$%s\n", cpy_cmd->value);
			cpy_cmd = cpy_cmd->next;
			cpy_token = cpy_token->next;
		}
		if (cpy_cmd->next && cpy_token->next && cpy_cmd->type == IN_OUT_FILENAME && cpy_cmd->next->type == IN_OUT_FILENAME && cpy_cmd->redirect_in_before == 1 
			&& (cpy_token->next->type == REDIRECT_IN || cpy_token->next->type == HERE_DOC))
		{	
			cpy_cmd->next->redirect_in_before = 1;
		}
		if (cpy_cmd->next && cpy_token->next && cpy_cmd->type == IN_OUT_FILENAME && cpy_cmd->redirect_in_before == 0 && (cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC))
			cpy_cmd->next->infile = ft_copy(cpy_cmd->value);
		if (cpy_cmd->next && ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	rest_ofthesteps_four(cmd, 0);
}

void	rest_ofthesteps_two(t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	cpy_token = token;
	if (cpy_cmd)
		cpy_cmd->first = 1;
	while (cpy_token)
	{
		if (cpy_cmd && (cpy_token->type == REDIRECT_IN
			|| cpy_token->type == HERE_DOC))
		{
			cpy_cmd->type = IN_OUT_FILENAME;
		}
		if (cpy_cmd->next 
			&& ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	rest_ofthesteps_three(token, cmd);
	return ;
}

void	rest_ofthesteps(t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
		{
			cpy_cmd->here_doc = 1;
		}
		if (cpy_cmd->next 
			&& ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	rest_ofthesteps_two(token, cmd);
	cpy_cmd = cmd;
	cpy_token = token;
	return ;
}
