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

static void	ft_has_space(t_token *token, char *line, int i)
{
	if (line[i] && is_space(line[i]))
		token->has_space = 1;
	else
		token->has_space = 0;
}

static char	*extract_word(char *line, int *i, int *token_type)
{
	int		start;
	char	*word;

	start = *i;
	*token_type = WORD;
	while (line[*i] && !is_space(line[*i]) && !is_symbol(line[*i])
		&& line[*i] != 34 && line[*i] != 39)
		(*i)++;
	word = ft_substr(line, start, *i - start);
	return (word);
}

static char	*extract_quoted_word(char *line, int *i, int *token_type)
{
	int		start;
	char	quote;
	char	*word;

	quote = line[*i];
	if (quote == 34)
		*token_type = DOUBLE_QUOTES;
	else
		*token_type = SINGLE_QUOTES;
	start = *i + 1;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
	{
		printf("Syntax error: unclosed quote\n");
		return (NULL);
	}
	word = ft_substr(line, start, *i - start);
	(*i)++;
	return (word);
}

t_token	*create_token_word(char *line, int *index)
{
	int		i;
	int		token_type;
	t_token	*token;
	char	*word;

	i = *index;
	skip_whitespaces(line, &i);
	if (line[i] == '\0')
		return (NULL);
	if (line[i] == 34 || line[i] == 39)
		word = extract_quoted_word(line, &i, &token_type);
	else
		word = extract_word(line, &i, &token_type);
	if (!word)
		return (NULL);
	*index = i;
	token = create_token(token_type, word);
	ft_has_space(token, line, i);
	free(word);
	return (token);
}
