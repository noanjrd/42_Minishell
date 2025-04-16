/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:41:34 by naankour          #+#    #+#             */
/*   Updated: 2025/04/16 15:41:34 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_symbol(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

t_token	*create_token_word(char *line, int *index)
{
	int	i;
	int	len;
	int	start;
	char	*word;

	i = *index;
	while (line[i] && (is_space(line[i])))
		i++;
	len = 0;
	start = i;
	while (line[i] && (!is_space(line[i]) && !is_symbol(line[i])))
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, &line[start], len + 1);
	*index = i;
	return(create_token(WORD, word));
}
