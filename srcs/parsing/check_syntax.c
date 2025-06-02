/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:27 by naankour          #+#    #+#             */
/*   Updated: 2025/04/17 12:29:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_redir_errors1(t_data *data, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if (curr->type == HERE_DOC || curr->type == REDIRECT_APPEND)
		{
			if (curr->next == NULL || curr->next->type == HERE_DOC
				|| curr->next->type == REDIRECT_APPEND)
			{
				if (curr->next == NULL)
					printf(NEW_LINE);
				else if (curr->next->type == HERE_DOC)
					printf(S_HERE_DOC);
				else if (curr->next->type == REDIRECT_APPEND)
					printf(APPEND);
				else
					printf(TOKEN, curr->next->value);
				data->exit_code = 2;
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static int	ft_check_redir_errors2(t_data *data, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if (curr->type == REDIRECT_IN || curr->type == REDIRECT_OUT)
		{
			if (curr->next == NULL || (curr->next->type != WORD
					&& curr->next->type != DOUBLE_QUOTES
					&& curr->next->type != SINGLE_QUOTES))
			{
				if (curr->next == NULL)
					printf(NEW_LINE);
				else
					printf(TOKEN, curr->value);
				data->exit_code = 2;
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static int	ft_check_pipe_errors(t_data *data, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if ((curr->next && curr->type == PIPE) && curr->next->type == PIPE)
		{
			data->exit_code = 2;
			return (printf(DOUBLE_PIPE), 1);
		}
		if ((curr == token && curr->type == PIPE)
			|| (curr->type == PIPE && curr->next == NULL))
		{
			data->exit_code = 2;
			return (printf(SINGLE_PIPE), 1);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_check_syntax_errors(t_data *data, t_token *token)
{
	if (ft_check_redir_errors1(data, token) == 1)
		return (1);
	else if (ft_check_redir_errors2(data, token) == 1)
		return (1);
	else if (ft_check_pipe_errors(data, token) == 1)
		return (1);
	return (0);
}
