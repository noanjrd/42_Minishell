/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:37:57 by njard             #+#    #+#             */
/*   Updated: 2025/05/12 12:06:34 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void printf_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd;
	int i = 0;

	while (current)
	{
		i = 0;
		printf("val=%s, in=%s, out=%s, fdin=%d, fdout=%d, here=%d, appd=%d, path_f=%d, built=%d, path=%s ,",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout,
			current->here_doc,
			current->red_append,
			current->path_found,
			current->builtin,
		current->path);
		printf("tab = ");
		if (current->tab)
		{
			while (current->tab && current->tab[i])
			{
				printf("| %s", current->tab[i]);
				i++;
			}
		}
		printf("\n");
		current = current->next;
	}
	printf("--------------------------------------------\n");
	return ;
}

void	number_of_commands(t_data *data)
{
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	while (cpy_cmd)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME)
			data->nb_of_commands++;
		cpy_cmd = cpy_cmd->next;
	}
	printf("{{%d}}", data->nb_of_commands);
	return ;
}

void	exec_builtin(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;
	char *value_temp;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->type == WORD || cpy_token->type == DOUBLE_QUOTES
			|| cpy_token->type == SINGLE_QUOTES)
		{
			cpy_token = builtin_check(data, cpy_token, cpy_token->value);
			if (data->builtin_found == 1)
			{
				cpy_cmd->builtin = 1;
				cpy_cmd = cpy_cmd->next;
			}
			data->builtin_found = 0;
		}
		else
			cpy_token = cpy_token->next;
	}
	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	check_path_exist(data, data->commands);
	printf_cmd(cpy_cmd);
	number_of_commands(data);
	real_exec(data);
}

void	fdin_check(t_data *data, t_cmd *cpy_cmd)
{
	if (cpy_cmd->here_doc == 0)
	{
		cpy_cmd->fdin = open(cpy_cmd->infile,O_RDONLY, 0700);
		if (cpy_cmd->fdin >= 0)
			cpy_cmd->check_fdin = 1;
	}
	else
	{
		cpy_cmd->fdin = data->fd_here_doc;
		cpy_cmd->check_fdin = 1;
	}
	return ;
}

void	exec_fdin(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->next && (cpy_token->type == REDIRECT_IN
			|| cpy_token->type == HERE_DOC))
			open_fdin(data, cpy_token, cpy_cmd);
		if (cpy_cmd && cpy_cmd->infile && cpy_cmd->fdin == -99)
			fdin_check(data, cpy_cmd);
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT
			|| cpy_token->type == REDIRECT_APPEND
			|| cpy_token->type == REDIRECT_IN
			|| cpy_token->type == HERE_DOC)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	exec_builtin(data);
}

void	exec_fdout(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token)
	{
		if (cpy_token->next && (cpy_token->next->type == REDIRECT_OUT
			|| cpy_token->next->type == REDIRECT_APPEND))
			open_fdout(data, cpy_token, cpy_cmd);
		if (cpy_token->type == PIPE
			|| cpy_token->type == REDIRECT_OUT
			|| cpy_token->type == REDIRECT_APPEND
			|| cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	exec_fdin(data);
}

void	exec(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	if (!data->tokens)
		return ;
	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	relink_commands(cpy_token, cpy_cmd);
	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	printf_cmd(cpy_cmd);
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
			here_doc(cpy_token, data);
		cpy_token = cpy_token->next;
	}
	exec_fdout(data);
}
