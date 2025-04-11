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

// creer des tokens

t_token	*lexer(char *line)
{
	int			i;
	t_token	*token;
	t_token	*head;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '<')
		{
			if (line [i + 1] == '<')
			{
				printf("here1\n");
				token = create_token(HERE_DOC, "<<");
				add_token(&head, token);
				i+=2;
			}
			else
			{
				printf("here2\n");
				token = create_token(REDIRECT_IN, "<");
				add_token(&head, token);
				i++;
			}
		}
		else if (line[i] == '>')
		{
			if (line [i + 1] == '>')
			{
				printf("here3\n");
				token = create_token(REDIRECT_APPEND, ">>");
				add_token(&head, token);
				i+=2;
			}
			else
			{
				printf("here4\n");
				token = create_token(REDIRECT_OUT, "<");
				add_token(&head, token);
				i++;
			}
		}
		else if (line[i] == '|')
		{
			token = create_token(PIPE, "|");
			add_token(&head,token);
			i++;
		}
		else if (line[i] == '$')
		{
			token = create_token(VARIABLE, "$");
			add_token(&head, token);
			i++;
		}
		else
		{
			while (line[i] == ' ')
				i++;
			token = create_token(WORD, &line[i]);
			add_token(&head, token);
			i++;
		}

	}
	print_tokens(head);
	return (head);
}
