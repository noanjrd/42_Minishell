/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:09:45 by naankour          #+#    #+#             */
/*   Updated: 2025/05/17 12:09:45 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	merge_tokens(t_token **token)
{
	t_token	*current;
	t_token	*new_token;
	t_token	*prev;
	t_token	*next_next;
	char	*merged;

	current = *token;
	while (current && current->next)
	{
		if ((current->type == WORD || current->type == DOUBLE_QUOTES
				|| current->type == SINGLE_QUOTES)
			&& (current->next->type == WORD || current->next->type
				== DOUBLE_QUOTES || current->next->type == SINGLE_QUOTES)
			&& current->has_space == 0)
		{
			merged = ft_join(current->value, current->next->value);
			if (!merged)
				return ;
			new_token = create_token(WORD, merged);
			free(merged);
			new_token->has_space = current->next->has_space;
			next_next = current->next->next;
			free(current->value);
			free(current->next->value);
			free(current->next);
			free(current);
			new_token->next = next_next;
			if (current == *token)
				*token = new_token;
			else
			{
				prev = *token;
				while (prev->next != current)
					prev = prev->next;
				prev->next = new_token;
			}
			current = new_token;
		}
		else
			current = current->next;
	}
}

void	reassign_index(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		tokens->index = i++;
		tokens = tokens->next;
	}
}
