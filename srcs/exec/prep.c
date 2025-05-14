/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:37:57 by njard             #+#    #+#             */
/*   Updated: 2025/05/14 16:32:30 by njard            ###   ########.fr       */
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
		printf("val=%s, in=%s, out=%s, fdin=%d, fdout=%d, i=%d, here=%d, appd=%d, path_f=%d, path=%s ,",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout,
			current->index,
			current->here_doc,
			current->red_append,
			current->path_found,
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


	check_path_exist(data, data->commands);
	// printf_cmd(cpy_cmd);
	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	
	printf_cmd(cpy_cmd);
	number_of_commands(data);
	real_exec(data);
}

void fdin_before(t_data *data, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	if (cmd->fdin > 0)
		return ;
	printf("BEFOOOORE\n");
	if (cmd->next->redirect_in_before == 0)
		return ;
	while (cpy_cmd && cpy_cmd->next && cpy_cmd->next->type == IN_OUT_FILENAME)
	{
		cpy_cmd = cpy_cmd->next;
	}
	free(cmd->infile);
	cmd->infile = ft_copy(cpy_cmd->value);
	// printf("+++++%s\n", cpy_cmd->value);
	cmd->fdin = open(cpy_cmd->value ,O_RDONLY, 0700);
	if (cmd->fdin > 0)
			cmd->check_fdin = 1;
	return ;
}

void fdin_after(t_data *data, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	printf("AFTRRRRR\n");
	if (cmd->next && cmd->next->type == WORD)
	{
		cpy_cmd->next->fdin = open(cpy_cmd->next->infile ,O_RDONLY, 0700);
		if (cpy_cmd->next->fdin > 0)
			cpy_cmd->next->check_fdin = 1;
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

void	exec_fdin(t_data *data)
{
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	while (cpy_token)
	{
		// if (cpy_token->next && (cpy_token->type == REDIRECT_IN
		// 	|| cpy_token->type == HERE_DOC))
		// 	open_fdin(data, cpy_token, cpy_cmd);
		if (cpy_cmd->next && cpy_cmd->infile && cpy_cmd->next->type == IN_OUT_FILENAME)
			fdin_before(data, cpy_cmd);
		if (cpy_cmd->type == IN_OUT_FILENAME && cpy_cmd->redirect_in_before == 0)
			fdin_after(data, cpy_cmd);
		// if (cpy_cmd && cpy_cmd->infile && cpy_cmd->fdin == -99)
		// 	fdin_check(data, cpy_cmd);
		if (cpy_cmd->next && (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT
			|| cpy_token->type == REDIRECT_APPEND
			|| cpy_token->type == REDIRECT_IN
			|| cpy_token->type == HERE_DOC))
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	// cpy_cmd = data->commands;
	// cpy_token = data->tokens;
	// printf_cmd(cpy_cmd);
	cpy_cmd = data->commands;
	cpy_token = data->tokens;
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
	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
			here_doc(cpy_token, data);
		cpy_token = cpy_token->next;
	}
	exec_fdout(data);
}
