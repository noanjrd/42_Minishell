/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:09:38 by naankour          #+#    #+#             */
/*   Updated: 2025/04/11 18:09:38 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	// if (!token)
	// 	return;
	token->type = type;
	token->value = strdup(value);
	token->next = NULL;
	token->index = index_t;
	index_t += 1;
	return(token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!head || !new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("type = %d, value = %s, index=%d\n", current->type, current->value, current->index);
		current = current->next;
	}
}
