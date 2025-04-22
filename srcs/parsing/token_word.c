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
int	is_quotes(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int	check_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
			i++;
		if (!line[i])
			return (0);
		}
		else
			i++;
	}
	return (1);
}

t_token	*create_token_word(char *line, int *index)
{
	int	i;
	int	len;
	int	start;
	char	*word;
	char	quote;

	i = *index;
	if (line[i] == 34 || line[i] == 39)
	{
		quote = line[i];
		start = i;
		i++;
		while (line[i] && (line[i] != quote))
			i++;
		if (line[i] == quote)
			i++;
		else
		{
			printf("quotes are not closed\n");
			exit(1);
		}
		len = i - start - 2;
		if (len <= 0)
			return(NULL);
		word = malloc(len + 1);
		if (!word)
			return (NULL);
		ft_strlcpy(word, &line[start + 1], len + 1);
		*index = i;
		if (quote == 34)
			return(create_token(DOUBLE_QUOTES, word));
		else
			return(create_token(SIMPLE_QUOTES, word));
	}
	while (line[i] && (is_space(line[i])))
		i++;
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

// t_token	*create_token_quotes(char *line, int *index)
// {
// 	int	i;
// 	int	len;
// 	int	end;
// 	int	start;
// 	char	*word;

// 	i = *index;
// 	len = 0;
// 	while (line[i] && (!is_quotes(line[i])))
// 		i++;
// 	start = i;
// 	while (line[i] && (!is_quotes(line[i])))
// 		i++;
// 	end = i;
// 	len = end - start;
// 	if (len == 0)
// 		return (NULL);
// 	word = malloc(len + 1);
// 	if (!word)
// 		return (NULL);
// 	ft_strlcpy(word, &line[start], len + 1);
// 	*index = i;
// 	return(create_token(WORD, word));
// }

