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
	int	single_quotes;
	int	double_quotes;

	while(line[i])
	{
		if (line[i] == 34)
			double_quotes++;
		else if (line[i] == 39)
			single_quotes++;
		i++;
	}
	if ((double_quotes % 2 != 0) || (single_quotes % 2 != 0))
		return (0);
	return (1);
}

t_token	*create_token_word(char *line, int *index)
{
	int	i;
	int	len;
	int	start;
	char	*word;

	if (check_quotes(line) == 0)
	{
		printf("eroooooooooooor\n");
		return(NULL);
	}
	i = *index;
	if (line[i] == 34)
	{
		start = i;
		i++;
		while (line[i] && (line[i] != 34))
			i++;
		if (line[i] == 34)
			i++;
		else
		{
			printf("double quotes are not closed");
			return (NULL);
		}
		len = i - start;
		if (len == 0)
			return(NULL);
		word = malloc(len + 1);
		if (!word)
			return (NULL);
		ft_strlcpy(word, &line[start], len + 1);
		*index = i;
	return(create_token(DOUBLE_QUOTES, word));
	}
	if (line[i] == 39)
	{
		start = i;
		i++;
		while (line[i] && (line[i] != 39))
			i++;
		if (line[i] == 39)
			i++;
		else
		{
			printf("simple quotes are not closed");
			exit(1);
		}
		len = i - start;
		if (len == 0)
			return(NULL);
		word = malloc(len + 1);
		if (!word)
			return (NULL);
		ft_strlcpy(word, &line[start], len + 1);
		*index = i;
	return(create_token(SIMPLE_QUOTES, word));
	}
	else
	{
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
	}
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

