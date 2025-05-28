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

int	ft_check_syntax_errors(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if ((curr->type == REDIRECT_IN || curr->type == REDIRECT_OUT
				|| curr->type == HERE_DOC || curr->type == REDIRECT_APPEND)
			&& (curr->next == NULL || (curr->next->type != WORD
					&& curr->next->type != DOUBLE_QUOTES
					&& curr->next->type != SINGLE_QUOTES)))
		{
			printf("syntax error near unexpected token ´%s'\n", curr->value);
			return (1);
		}
		if ((curr->next && curr->type == PIPE) && curr->next->type == PIPE)
			return (printf("syntax error near unexpected token ´||'\n"), 1);
		if ((curr == token && curr->type == PIPE)
			|| (curr->type == PIPE && curr->next == NULL))
			return (printf("syntax error near unexpected token ´||'\n"), 1);
		curr = curr->next;
	}
	return (0);
}
