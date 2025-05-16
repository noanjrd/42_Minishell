/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:31:52 by naankour          #+#    #+#             */
/*   Updated: 2025/04/09 15:31:52 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

t_token	*handle_symbol(char *line, int *i)
{
	t_token	*token;

	token = NULL;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		token = create_token(HERE_DOC, "<<");
		(*i) += 2;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		token = create_token(REDIRECT_APPEND, ">>");
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		token = create_token(REDIRECT_IN, "<");
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		token = create_token(REDIRECT_OUT, ">");
		(*i)++;
	}
	else if (line[*i] == '|')
	{
		token = create_token(PIPE, "|");
		(*i)++;
	}
	return(token);
}

t_token *lexer(char *line)
{
	int i = 0;

	t_token *head;
	t_token *token;

	head = NULL;
	token = NULL;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (line[i] == '\0')
			break;
		token = NULL;
		if (is_symbol(line[i]))
			token = handle_symbol(line, &i);
		else
			token = create_token_word(line, &i);
		if (!token)
		{
			// printf("Lexer error near '%.10s'\n", line + i);
			free_token_list(head);
			return NULL;
		}
		add_token(&head, token);
	}
	// print_tokens(head);
	return head;
}





