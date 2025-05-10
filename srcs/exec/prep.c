/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:37:57 by njard             #+#    #+#             */
/*   Updated: 2025/05/10 17:54:02 by naankour         ###   ########.fr       */
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
		printf("val = %s, in = %s, out = %s, fdin = %d, fdout = %d, i = %d, here = %d, appd = %d, path_f = %d, ",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout,
			current->fdout,
		current->here_doc,
		current->red_append,
		current->path_found);
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

void	exec_builtin(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	// printf_cmd(cpy_cmd);
	// print_tokens(cpy_token);
	while (cpy_token)
	{
		if (cpy_token->type == WORD || cpy_token->type == DOUBLE_QUOTES || cpy_token->type == SINGLE_QUOTES)
		{
			cpy_token = builtin(data, cpy_token, cpy_token->value);
		}
		else
			cpy_token = cpy_token->next;
	}
	check_path_exist(data, data->commands);
	// printf_cmd(cpy_cmd);

}

void	exec_fdin(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	// printf_cmd(cpy_cmd);
	while (cpy_token)
	{
		if (cpy_token->next && (cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC))
			open_fdin(data, cpy_token, cpy_cmd);
		if (cpy_cmd && cpy_cmd->infile && cpy_cmd->fdin == -99)
		{
			if (cpy_cmd->here_doc == 0)
				cpy_cmd->fdin = open(cpy_cmd->infile, O_WRONLY | O_CREAT , 0644);
			if (cpy_cmd->here_doc == 1)
				cpy_cmd->fdin = data->fd_here_doc;
		}
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
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
		if (cpy_token->next && (cpy_token->next->type == REDIRECT_OUT || cpy_token->next->type == REDIRECT_APPEND))
			open_fdout(data, cpy_token, cpy_cmd);
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	exec_fdin(data);
}

void	exec(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	relink_commands(cpy_token, cpy_cmd);
	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	// printf_cmd(cpy_cmd);
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
			here_doc(cpy_token, data);
		cpy_token = cpy_token->next;
	}
	exec_fdout(data);
}
