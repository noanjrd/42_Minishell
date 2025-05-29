/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:37:48 by njard             #+#    #+#             */
/*   Updated: 2025/05/29 13:29:34 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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


void	rest_ofthesteps_minus_one(t_data *data)
{
	t_token	*cpy_token;
	t_cmd	*cpy_cmd;

	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token)
	{
		if (cpy_token && (cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND))
		{
			cpy_cmd->type = IN_OUT_FILENAME;
			cpy_cmd->red_out = 1;
			if (cpy_token->type == REDIRECT_APPEND)
				cpy_cmd->red_append = 1;
		}
		if (ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	rest_ofthesteps(data->tokens, data->commands);
}

void	assign_value(t_cmd *new_cmd, t_token *cpy_token, int i)
{
	new_cmd->fdout = -99;
	new_cmd->fdin = -99;
	new_cmd->check_fdout = 0;
	new_cmd->check_fdin = 0;
	new_cmd->here_doc = 0;
	new_cmd->red_append = 0;
	new_cmd->deleted = 0;
	new_cmd->first = 0;
	new_cmd->index = i;
	new_cmd->pid = -1;
	new_cmd->fdpipe = malloc(3 * sizeof(int));
	new_cmd->fdpipe[0] = -1;
	new_cmd->fdpipe[1] = -1;
	new_cmd->prev_fdpipe =NULL;
	new_cmd->end = 0;
	new_cmd->value = ft_copy(cpy_token->value);
	new_cmd->infile = NULL;
	new_cmd->type = WORD;
	new_cmd->path = NULL;
	new_cmd->tab = NULL;
	new_cmd->redirect_in_before = 0;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	new_cmd->red_out = 0;
}

void	make_commands(t_data *data, t_cmd *head, t_cmd *current, t_cmd *new_cmd)
{
	t_token *cpy_token;
	char *fdin;

	fdin = NULL;
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->type == WORD || cpy_token->type == SINGLE_QUOTES || cpy_token->type == DOUBLE_QUOTES)
		{
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				return;
			assign_value(new_cmd, cpy_token, cpy_token->index);
			if (!head)
				head = new_cmd;
			else
				current->next = new_cmd;
			current = new_cmd;
		}
		if (current && cpy_token->next && (cpy_token->next->type == REDIRECT_APPEND || cpy_token->next->type == REDIRECT_OUT))
				current->outfile = ft_copy(cpy_token->next->next->value);
		cpy_token = cpy_token->next;
	}
	data->commands = head;
	rest_ofthesteps_minus_one(data);
}
