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

#include "../../includes/minishell.h"

void	merge_tokens(t_token **token)
{
	t_token	*current;
	char	*merged;
	t_token	*new_token;
	t_token	*prev;

	// prev = NULL;
	current = *token;
	while (current && current->next)
	{
		if ((current->type == WORD || current->type == DOUBLE_QUOTES || current->type == SINGLE_QUOTES)
		&& (current->next->type == WORD || current->next->type == DOUBLE_QUOTES || current->next->type == SINGLE_QUOTES) && current->has_space == 0)
		{
			// je merge
			merged = ft_join(current->value, current->next->value);
			if (!merged)
				return;
			new_token = create_token(WORD, merged);
			new_token->has_space = current->next->has_space; // pour savoir si je dois mettre un espace lors de laffichage je recupere has_space du dernier token
			free(merged);
			new_token->next = current->next->next; //jintegre new_token a la liste en le liant au token suivant current->next
			//mettre a jour la tête de la liste si cetait le premier token de la liste
			// printf("%s", current->value);
			free(current->value);
			free(current);
			free(current->next->value);
			free(current->next);
			if (current == *token)
			*token = new_token;
			//raccorder avec le token precedent sil y en un avant
			//je suis actuellement en train de remplacer current par un new_token donc il faut que le token precedent de current soit relie a new_token
			else
			{
				prev = *token;
				// je parcours la liste tant que je nai pas trouve prev de current donc il faut que prev-> next soit egal a current
				while(prev->next != current) // quand prev->next == current ca veut dire que le suivant apres prev est current
				prev = prev->next;			//donc a la place de current et donc de pv_next je dois mettre new_token
				prev->next = new_token;
			}
			current = new_token;
		}
		else
		current = current->next; //je passe au suivant
	}
	// print_tokens(*token);
}


void	reassign_index(t_token *tokens)
{
	int		i;

	i = 0;
	while(tokens)
	{
		tokens->index = i++;
		tokens = tokens->next;
	}
}


