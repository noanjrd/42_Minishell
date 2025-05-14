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

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof (char) * (ft_strlen(src) +1));
	if (!dest)
	{
		return (NULL);
	}
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_token *create_token(t_token_type type, char *value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);

	token->type = type;
	token->value = ft_strdup(value);
	// printf("token value = %s while create\n", token->value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	token->index = index_t++;
	return (token);
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
void	free_token_list(t_token *head)
{
	t_token	*temp;

	// printf("HELLO SIR\n");
	while (head)
	{
		// printf("HELLO CHEF\n");
		temp = head;
		head = head->next;
		if (temp->value)
		{
			// printf("token value = %s while free\n", temp->value);
			free(temp->value);
		}
		free(temp);
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
