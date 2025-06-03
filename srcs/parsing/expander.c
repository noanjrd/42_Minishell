/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:36:38 by naankour          #+#    #+#             */
/*   Updated: 2025/05/05 13:36:38 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*remove_token(t_token *token, t_token *prev, t_token *to_remove)
{
	if (!prev)
		token = to_remove->next;
	else
		prev->next = to_remove->next;
	free(to_remove->value);
	free(to_remove);
	return (token);
}

static void	expand_token(t_token *token, t_data *data)
{
	char	*new_value;

	new_value = new_token_value(token->value, data);
	if (!new_value)
	{
		free(token->value);
		token->value = NULL;
		return ;
	}
	if (new_value && new_value[0] == '\0' && token->type == WORD)
	{
		free(new_value);
		free(token->value);
		token->value = NULL;
	}
	else
	{
		free(token->value);
		token->value = new_value;
	}
}

static int	needs_expansion(t_token *token, t_token *prev)
{
	if (!token || !token->value)
		return (0);
	if (prev && prev->type == HERE_DOC)
		return (0);
	if (((token->type == WORD) || (token->type == DOUBLE_QUOTES))
		&& ft_strchr(token->value, '$'))
		return (1);
	return (0);
}

t_token	*expander(t_token *token, t_data *data)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = token;
	prev = NULL;
	while (current)
	{
		if (needs_expansion(current, prev) == 1)
		{
			expand_token(current, data);
			if (current->value == NULL)
			{
				next = current->next;
				token = remove_token(token, prev, current);
				current = next;
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
	return (token);
}
