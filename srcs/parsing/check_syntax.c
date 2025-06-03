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

static int	ft_check_pipe_errors(t_data *data, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if ((curr->next && curr->type == PIPE) && curr->next->type == PIPE)
		{
			data->exit_code = 2;
			ft_putstr_fd(DOUBLE_PIPE, 2);
			return (1);
		}
		if ((curr == token && curr->type == PIPE)
			|| (curr->type == PIPE && curr->next == NULL))
		{
			data->exit_code = 2;
			ft_putstr_fd(SINGLE_PIPE, 2);
			return (1);
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
				ft_putstr_fd(TOKEN, 2);
				if (curr->next == NULL)
					ft_putstr_fd("newline", 2);
				else
					ft_putstr_fd(curr->next->value, 2);
				ft_putstr_fd("'\n", 2);
				data->exit_code = 2;
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

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
				ft_putstr_fd(TOKEN, 2);
				if (curr->next == NULL)
					ft_putstr_fd("newline", 2);
				else
					ft_putstr_fd(curr->next->value, 2);
				ft_putstr_fd("'\n", 2);
				data->exit_code = 2;
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static int	ft_check_redir_errors(t_data *data, t_token *token)
{
	if (ft_check_redir_errors1(data, token))
		return (1);
	if (ft_check_redir_errors2(data, token))
		return (1);
	return (0);
}

int	ft_check_syntax_errors(t_data *data, t_token *token)
{
	if (ft_check_redir_errors(data, token) == 1)
		return (1);
	else if (ft_check_pipe_errors(data, token) == 1)
		return (1);
	return (0);
}
