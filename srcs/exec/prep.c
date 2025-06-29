/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:37:57 by njard             #+#    #+#             */
/*   Updated: 2025/06/05 15:30:11 by njard            ###   ########.fr       */
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
		printf("val=%s, in=%s, out=%s, fdin=%d, fdout=%d, i=%d, here=%d, appd=%d, path=%s, end=%d, ",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout,
			current->index,
			current->here_doc,
			current->red_append,
		current->path,
	current->end);
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
	t_cmd	*cpy_cmd;

	cpy_cmd = data->commands;
	while (cpy_cmd)
	{
		if (cpy_cmd->type != IN_OUT_FILENAME
			|| cpy_cmd->red_out == 1)
			data->nb_of_commands++;
		cpy_cmd = cpy_cmd->next;
	}
	return ;
}

void	details_before_exec(t_data *data)
{
	check_path_exist(data, data->commands);
	number_of_commands(data);
	// printf_cmd(data->commands);
	exec(data);
}

void	exec_fdin(t_data *data)
{
	t_token	*cpy_token;
	t_cmd	*cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_cmd->next && cpy_cmd->infile
			&& cpy_cmd->next->type == IN_OUT_FILENAME)
			fdin_before(data, cpy_cmd);
		if (cpy_cmd->type == IN_OUT_FILENAME
			&& cpy_cmd->redirect_in_before == 0)
			fdin_after(data, cpy_cmd);
		if (cpy_cmd->next
			&& (cpy_token->type == PIPE
				|| cpy_token->type == REDIRECT_OUT
				|| cpy_token->type == REDIRECT_APPEND
				|| cpy_token->type == REDIRECT_IN
				|| cpy_token->type == HERE_DOC))
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	details_before_exec(data);
}

void	exec_fdout(t_data *data)
{
	fd_error(data, 0);
	open_fdout(data->tokens, data->commands);
	exec_fdin(data);
}

void	exec_prep(t_data *data)
{
	t_token	*cpy_token;
	t_cmd	*cpy_cmd;

	if (!data->tokens)
		return ;
	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	relink_commands(cpy_token, cpy_cmd);
	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token && g_exit_code_signal != -99)
	{
		if (cpy_token->type == HERE_DOC && g_exit_code_signal != -99)
			here_doc(cpy_token, data);
		cpy_token = cpy_token->next;
	}
	if (g_exit_code_signal != -99)
		exec_fdout(data);
	else
	{
		g_exit_code_signal = 0;
		data->exit_code = 130;
	}
}

// void printf_cmd(t_cmd *cmd)
// {
// 	t_cmd *current = cmd;
// 	int i = 0;

// 	while (current)
// 	{
// 		i = 0;
// 		printf("val=%s, in=%s, out=%s, fdin=%d,
// fdout=%d, i=%d, here=%d, appd=%d, path=%s, end=%d, ",
// 			current->value,
// 			current->infile ? current->infile : "NULL",
// 			current->outfile ? current->outfile : "NULL",
// 			current->fdin,
// 			current->fdout,
// 			current->index,
// 			current->here_doc,
// 			current->red_append,
// 		current->path,
// 	current->end);
// 		printf("tab = ");
// 		if (current->tab)
// 		{
// 			while (current->tab && current->tab[i])
// 			{
// 				printf("| %s", current->tab[i]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 		current = current->next;
// 	}
// 	printf("--------------------------------------------\n");
// 	return ;
// }