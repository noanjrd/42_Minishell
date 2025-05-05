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
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if ((current->type == REDIRECT_IN || current->type == REDIRECT_OUT || current->type == HERE_DOC || current->type == REDIRECT_APPEND)
			&& (current->next == NULL || current->next->type != WORD))
		{
			printf("syntax error near unexpected token ´%s'\n", current->value);
			return (1);
		}
		if ((current->next && current->type == PIPE) && current->next->type == PIPE)
		{
			printf("syntax error near unexpected token ´||'\n");
			return (1);
		}
		if ((current == token && current->type == PIPE) || (current->type == PIPE && current->next == NULL))
		{
			printf("syntax error near unexpected token ´||'\n");
			return (1);
		}
		current = current->next;
	}
	return (0);
}
