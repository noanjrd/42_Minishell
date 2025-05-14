/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:37:48 by njard             #+#    #+#             */
/*   Updated: 2025/05/14 16:37:42 by njard            ###   ########.fr       */
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
			if (cpy_cmd->next)
				cpy_cmd->next->here_doc = 1;
		}
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		// printf("{token %s, cmd%s}\n", cpy_token->value, cpy_cmd->value);
		if (cpy_cmd && cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			// printf("laaa\n");
			cpy_cmd->type = IN_OUT_FILENAME;
		}
		if (cpy_cmd->next && ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		printf("{token %s, cmd %s}\n", cpy_token->value, cpy_cmd->value);
		if (cpy_cmd && cpy_token->next && cpy_token->next->next && cpy_cmd->type != IN_OUT_FILENAME && (cpy_token->next->type == REDIRECT_IN || cpy_token->next->type == HERE_DOC))
		{
			cpy_cmd->next->redirect_in_before = 1;
			cpy_cmd->infile = ft_copy(cpy_token->next->next->value);
			printf("laaa\n");
			cpy_cmd = cpy_cmd->next;
			cpy_token = cpy_token->next;
		}
		// printf("{!!!!!token %s, cmd %s}\n", cpy_token->value, cpy_cmd->value);
		if (cpy_cmd->next && cpy_token->next && cpy_cmd->type == IN_OUT_FILENAME && cpy_cmd->next->type == IN_OUT_FILENAME && cpy_cmd->redirect_in_before == 1 
			&& (cpy_token->next->type == REDIRECT_IN || cpy_token->next->type == HERE_DOC))
		{
			printf("sasasasa\n");
			cpy_cmd->next->redirect_in_before = 1;
		}
		if (cpy_cmd->next && cpy_token->next && cpy_cmd->type == IN_OUT_FILENAME && cpy_cmd->redirect_in_before == 0 && (cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC))
		{
			cpy_cmd->next->infile = ft_copy(cpy_cmd->value);
			printf("papapa\n");
		}
		if (cpy_cmd->next && ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	return ;
}

void	assign_value(t_cmd *new_cmd, t_token *cpy_token, int i)
{
	new_cmd->fdout = -99;
	new_cmd->fdin = -99;
	new_cmd->check_fdout = 0;
	new_cmd->here_doc = 0;
	new_cmd->red_append = 0;
	new_cmd->index = i;
	new_cmd->path_found = 0;
	new_cmd->builtin = 0;
	new_cmd->fdpipe = malloc(3 * sizeof(int));
	new_cmd->prev_fdpipe = NULL;
	new_cmd->value = ft_copy(cpy_token->value);
	new_cmd->infile = NULL;
	new_cmd->type = WORD;
	new_cmd->path = NULL;
	new_cmd->tab = NULL;
	new_cmd->redirect_in_before = 0;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	return ;
}

void	make_commands(t_data *data, t_cmd *head, t_cmd *current, t_cmd *new_cmd)
{
	t_token *cpy_token;
	char *fdin;
	int check;
	int out;
	int i;

	i = 0;
	out = 0;
	check = 0;
	fdin = NULL;
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token && (cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN))
		{
			check = 1;
			fdin = cpy_token->next->value;
		}
		if (cpy_token && (cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND))
			out = 1;
		if (cpy_token->type == WORD || cpy_token->type == SINGLE_QUOTES || cpy_token->type == DOUBLE_QUOTES)
		{
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				return;
			assign_value(new_cmd, cpy_token, i);
			// if (fdin && !(cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN))
			// {
			// 	if (current)
			// 		current->type = IN_OUT_FILENAME;
			// }
			// if (fdin && check == 3 && !(cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN))
			// {
			// 	new_cmd->infile = ft_copy(fdin);
			// 	if (current)
			// 		current->type = IN_OUT_FILENAME;
			// 	fdin = NULL;
			// 	check = 0;
			// }
			// if (check == 3 && cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN)
			// 	check = 0;
			if (out == 1)
			{
				new_cmd->type = IN_OUT_FILENAME;
				out = 0;
			}
			if (!head)
				head = new_cmd;
			else
				current->next = new_cmd;
			current = new_cmd;
		}
		if (cpy_token->next && (cpy_token->next->type == REDIRECT_APPEND || cpy_token->next->type == REDIRECT_OUT))
		{
			if (current)
				current->outfile = ft_copy(cpy_token->next->next->value);
		}
		if (check == 2)
			check =3;
		if (check == 1)
			check = 2;
		i++;
		cpy_token = cpy_token->next;
	}
	data->commands = head;
	rest_ofthesteps(data->tokens, head);
}
