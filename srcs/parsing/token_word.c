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

int index_t = 0;

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_symbol(char c)
{
	int	i;

	i = 0;
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;

	if (!s)
		return (NULL);
	if (start >= strlen(s))
		return (strdup(""));
	if (len > strlen(s + start))
		len = strlen(s + start);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
t_token *create_token_word(char *line, int *index)
{
	int		i;
	int		start;
	char	quote;
	int		token_type;
	t_token	*token;
	char	*word;

	i = *index;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (NULL);
	if (line[i] == '\'' || line[i] == '"')
	{
		quote = line[i];
		if (quote == '"')
			token_type = DOUBLE_QUOTES;
		else
			token_type = SINGLE_QUOTES;
		start = i + 1;
		i++;
		while (line[i] && line[i] != quote)
			i++;
		if (line[i] != quote)
		{
			printf("Syntax error: unclosed quote\n");
			return (NULL);
		}
		word = ft_substr(line, start, i - start);
		if (!word)
			return (NULL);
		i++;
	}
	else
	{
		start = i;
		token_type = WORD;
		while (line[i] && !is_space(line[i]) && !is_symbol(line[i]) &&
				line[i] != '\'' && line[i] != '"')
			i++;
		word = ft_substr(line, start, i - start);
		if (!word)
			return (NULL);
	}
	*index = i;
	token = create_token(token_type, word);
	if (line[i] && is_space(line[i]))
		token->has_space = 1;
	else
		token->has_space = 0;
	free(word);
	return (token);
}


//"e"'c'ho hello

// apres avoir fait l expansion
// jai plusieurs tokens           e c ho hello

// je fais une fonction qui va parcourir la liste de tokens, qui va les merge en fonction de is_space ?
// while tokens if token->has_space cest un seul token donc lajouter dans un token dont le type est word sinon !has_space on merge

// token -> token -> token -> token -> token -> NULL



// gerer aussi le cas suivant :
// naankour@c2r11p1:~/minimerge2$ echo "$dawdaw" hello
//  hello
// naankour@c2r11p1:~/minimerge2$ echo $dawdaw hello
// hello
// naankour@c2r11p1:~/minimerge2$ echo $dawdaw hello
// et renvoyer cette nouvelle liste de tokens