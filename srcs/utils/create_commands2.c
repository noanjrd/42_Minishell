/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:37:48 by njard             #+#    #+#             */
/*   Updated: 2025/06/05 15:29:56 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_condition_red(t_token *cpy_token)
{
	if (cpy_token->type == REDIRECT_IN
		|| cpy_token->type == HERE_DOC)
		return (1);
	return (0);
}

static int	ft_condition_red_in(t_token *cpy_token)
{
	if (cpy_token->type == REDIRECT_IN
		|| cpy_token->type == HERE_DOC)
		return (1);
	return (0);
}

void	ft_rest_condition(t_cmd *cpy_cmd, t_token *cpy_token)
{
	if (cpy_cmd->next && cpy_token->next
		&& cpy_cmd->type == IN_OUT_FILENAME
		&& cpy_cmd->next->type == IN_OUT_FILENAME
		&& cpy_cmd->redirect_in_before == 1
		&& ft_condition_red_in(cpy_token->next) == 1)
		cpy_cmd->next->redirect_in_before = 1;
	if (cpy_cmd->next && cpy_token->next
		&& cpy_cmd->type == IN_OUT_FILENAME
		&& cpy_cmd->redirect_in_before == 0
		&& ft_condition_red_in(cpy_token) == 1)
		cpy_cmd->next->infile = ft_copy(cpy_cmd->value);
	return ;
}

void	rest_ofthesteps_three(t_token *token, t_cmd *cmd)
{
	t_token	*cpy_token;
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		if (cpy_cmd && cpy_token->next
			&& cpy_token->next->next
			&& cpy_cmd->type != IN_OUT_FILENAME
			&& ft_condition_red(cpy_token->next) == 1)
		{
			// printf("%s\n", cpy_cmd->value);
			// printf("%s\n", cpy_token->value);
			cpy_cmd->next->redirect_in_before = 1;
			cpy_cmd->infile = ft_copy(cpy_token->next->next->value);
			cpy_cmd = cpy_cmd->next;
			cpy_token = cpy_token->next;
		}
		ft_rest_condition(cpy_cmd, cpy_token);
		if (cpy_cmd->next && ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
			cpy_cmd = cpy_cmd->next;
		cpy_token = cpy_token->next;
	}
	rest_ofthesteps_four(cmd, 0);
}

void	rest_ofthesteps_two(t_token *token, t_cmd *cmd)
{
	t_token	*cpy_token;
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
