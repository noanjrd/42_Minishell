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

t_token *create_token_word(char *line, int *index)
{
	int i = *index;
	int len = 0;
	int in_quotes = 0;
	char quote;
	int token_type = WORD;
	char *word;
	t_token *token;

	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (NULL);
	word = malloc(ft_strlen(&line[i]) + 1);
	if (!word)
		return (NULL);

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote = line[i];
				i++;
				if (quote == '"')
					token_type = DOUBLE_QUOTES;
				else
					token_type = SINGLE_QUOTES;
			}
			else if (line[i] == quote)
			{
				in_quotes = 0;
				i++;
			}
			else
			{
				word[len] = line[i];
				len++;
				i++;
			}
		}
		else if (!in_quotes && (is_space(line[i]) || is_symbol(line[i])))
			break;
		else
		{
			word[len] = line[i];
			len++;
			i++;
		}
	}
	if (in_quotes)
	{
		printf("Syntax error: unclosed quote\n");
		free(word);
		return (NULL);
	}
	word[len] = '\0';
	*index = i;
	token = create_token(token_type, word);
	free(word);
	return (token);
}

// t_token *create_token_word(char *line, int *index)
// {
// 	int		i = *index;
// 	int		len = 0;
// 	int		in_quotes = 0;
// 	char	quote;
// 	int		token_type = WORD;
// 	char	*word;
// 	t_token	*token;

// 	while (line[i] && is_space(line[i]))
// 		i++;
// 	if (line[i] == '\0')
// 		return (NULL);

// 	word = malloc(ft_strlen(&line[i]) + 1);
// 	if (!word)
// 		return (NULL);

// 	while (line[i])
// 	{
// 		if ((line[i] == '\'' || line[i] == '"'))
// 		{
// 			if (!in_quotes)
// 			{
// 				in_quotes = 1;
// 				quote = line[i++];
// 				token_type = (quote == '"') ? DOUBLE_QUOTES : SINGLE_QUOTES;
// 			}
// 			else if (line[i] == quote)
// 			{
// 				in_quotes = 0;
// 				i++;
// 			}
// 			else
// 				word[len++] = line[i++];
// 		}
// 		else if (!in_quotes && (is_space(line[i]) || is_symbol(line[i])))
// 			break;
// 		else
// 			word[len++] = line[i++];
// 	}

// 	if (in_quotes)
// 	{
// 		printf("Syntax error: unclosed quote\n");
// 		free(word);
// 		return (NULL);
// 	}
// 	word[len] = '\0';
// 	*index = i;

// 	token = create_token(token_type, word);
// 	free(word); // safe: create_token does strdup
// 	return (token);
// }

// t_token *create_token_word(char *line, int *index)
// {
// 	int		i;
// 	int		len;
// 	char	*word;
// 	char	quote;
// 	int		in_quotes;
// 	int		token_type;
// 	t_token	*token;

// 	i = *index;
// 	while (line[i] && is_space(line[i]))
// 		i++;
// 	if (line[i] == '\0')
// 		return (NULL);
// 	token_type = WORD;
// 	in_quotes = 0;
// 	len = 0;
// 	word = malloc(ft_strlen(&line[i]) + 1);
// 	if (!word)
// 		return (NULL);
// 	while (line[i])
// 	{
// 		if ((line[i] == '\'' || line[i] == '"'))
// 		{
// 			if (in_quotes == 0)
// 			{
// 				in_quotes = 1;
// 				quote = line[i];
// 				if (quote == '"')
// 					token_type = DOUBLE_QUOTES;
// 				else if (quote == '\'')
// 					token_type = SINGLE_QUOTES;
// 				i++;
// 			}
// 			else if (line[i] == quote)
// 			{
// 				in_quotes = 0;
// 				i++;
// 			}
// 			else
// 				word[len++] = line[i++];
// 		}
// 		else if (!in_quotes && (is_space(line[i]) || is_symbol(line[i])))
// 			break;
// 		else
// 			word[len++] = line[i++];
// 	}
// 	if (in_quotes)
// 	{
// 		printf("Syntax error: unclosed quote\n");
// 		free(word);
// 		return (NULL);
// 	}
// 	word[len] = '\0';
// 	*index = i;
// 	token = create_token(token_type, word);
// 	free(word);
// 	return (token);
// }

// int	is_quotes(char c)
// {
// 	if (c == 34)
// 		return (1);
// 	return (0);
// }

// int	check_quotes(char *line)
// {
// 	int		i;
// 	char	quote;

// 	i = 0;
// 	quote = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == 34 || line[i] == 39)
// 		{
// 			quote = line[i];
// 			i++;
// 			while (line[i] && line[i] != quote)
// 			i++;
// 		if (!line[i])
// 			return (0);
// 		}
// 		else
// 			i++;
// 	}
// 	return (1);
// }

// t_token *create_token_word(char *line, int *index)
// {
// 	int	i;
// 	int	len;
// 	int	start;
// 	char	*word;
// 	char	quote;
// 	int		in_quotes;

// 	in_quotes = 0;
// 	i = *index;
// 	while (line[i] && is_space(line[i]))
// 		i++;
// 	if (line[i] == '\0')
// 		return (NULL);
// 	start = i;
// 	len = 0;
// 	quote = 0;
// 	if (line[i] == 34 || line[i] == 39)
// 	{
// 			in_quotes = 1;
// 			quote = line[i++];
// 			start = i;
// 	}
// 	word = malloc(ft_strlen(&line[i]) + 1);
// 	if (!word)
// 		return(NULL);
// 	while(line[i] && (in_quotes || (!is_space(line[i]) && !is_symbol(line[i]))))
// 	{
// 		if (in_quotes && line[i] == quote)
// 		{
// 			in_quotes = 0;
// 			i++;
// 			break;
// 		}
// 		word[len++] = line[i++];
// 	}
// 	if (in_quotes)
// 	{
// 		printf("quotes are not closed\n");
// 		free(word);
// 		exit(1);
// 	}
// 	word[len] = '\0';
// 	*index = i;
// 	if (quote)
// 		return (create_token(DOUBLE_QUOTES, word));
// 	else
// 		return(create_token(WORD, word));
// }

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

