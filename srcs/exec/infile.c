/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:18:56 by njard             #+#    #+#             */
/*   Updated: 2025/05/11 10:44:37 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *relink_fdin_cmd(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;
	t_cmd	*start;
	t_cmd *current;

	start = cmd;
	free(cmd->value);
	free(cmd->infile);
	free(cmd->outfile);
	cmd->value = ft_copy(cpy_cmd->value);
	cmd->infile = ft_copy(cpy_cmd->infile);
	cmd->outfile = ft_copy(cpy_cmd->outfile);
	current = cmd->next;
	cmd->next = NULL;
	while (current && current->index != cpy_cmd->index)
	{
		temp = current->next;
		free(current->value);
		free(current->infile);
		free(current->outfile);
		free(current);
		current = temp;
	}
	if (current && current->index == cpy_cmd->index)
	{
		free(current->value);
		free(current->infile);
		free(current->outfile);
		temp = current->next;
		free(current);
		cmd->next = temp;
	}

	return start;
}

t_token *relink_fdin_token(t_token *token, t_token *cpy_token)
{
	t_token	*temp;
	t_token	*start;
	t_token *current;

	start = token;
	free(token->value);
	token->value = ft_copy(cpy_token->value);
	token->type = cpy_token->type;
	if (!token->value)
		return NULL;
	current = token->next;
	token->next = NULL;
	while (current && current->index != cpy_token->index)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	if (current && current->index == cpy_token->index)
	{
		free(current->value);
		temp = current->next;
		free(current);
		token->next = temp;
	}
	return start;
}

void	open_fdin(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd	*cpy_cmd;
	int fdin;
	cpy_token = token;
	cpy_cmd = cmd;
	int check = 0;

	// printf("|%s|\n", cpy_token->value);
	// printf("|%s|\n", cpy_token->next->value);
	while (cpy_token->next->next && cpy_cmd->next->next && (cpy_cmd->next->type == IN_OUT_FILENAME || cpy_token->next->next->type == HERE_DOC || cpy_token->next->next->type == REDIRECT_IN))
	{
		check = 1;
		// printf("{%s\n", cpy_cmd->value);
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next->next;
	}
	// printf("%s\n", cpy_token->value);
	// printf("%s\n", cpy_token->next->value);
	// printf("%s\n", cpy_cmd->value);
	// printf("%s\n", cpy_cmd->next->value);
	if (check == 1)
	{
		// printf("relink\n");
		token =  relink_fdin_token(token, cpy_token);
		cmd = relink_fdin_cmd(cmd, cpy_cmd);
	}
	return ;
}
