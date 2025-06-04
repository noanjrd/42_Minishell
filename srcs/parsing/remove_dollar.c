/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casparticulier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:31:44 by naankour          #+#    #+#             */
/*   Updated: 2025/06/02 16:31:44 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*remove_dollar(t_token **head, t_token *prev, t_token *curr)
{
	t_token	*to_delete;
	t_token	*next_token;

	to_delete = curr;
	next_token = curr->next;
	if (prev)
		prev->next = next_token;
	else
		*head = next_token;
	free(to_delete->value);
	free(to_delete);
	return (next_token);
}

static int	should_remove_dollar(t_token *curr)
{
	if (!curr || !curr->next)
		return (0);
	if (curr->type == WORD && strcmp(curr->value, "$") == 0
		&& (curr->next->type == DOUBLE_QUOTES
			|| curr->next->type == SINGLE_QUOTES))
		return (1);
	return (0);
}

t_token	*ft_dollar_quotes(t_token *tokens)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*head;

	prev = NULL;
	curr = tokens;
	head = tokens;
	while (curr && curr->next)
	{
		if (should_remove_dollar(curr) == 1)
			curr = remove_dollar(&head, prev, curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (head);
}
