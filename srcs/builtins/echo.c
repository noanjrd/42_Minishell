/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:25:03 by njard             #+#    #+#             */
/*   Updated: 2025/05/28 12:31:09 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *update_echo_struct(t_token *token)
{
	while (token && (token->type == WORD
		|| token->type == SINGLE_QUOTES
		|| token->type == DOUBLE_QUOTES))
		token = token->next;
	return (token);
}

static int ft_condition(t_token *copy_token)
{
	if (copy_token->next &&
		(copy_token->next->type == WORD
			|| copy_token->next->type == SINGLE_QUOTES
			|| copy_token->next->type == DOUBLE_QUOTES))
		return (1);
	return (0);
}

t_token	*ft_check_n(t_token *copy_token, int *n)
{
	int i;

	i = 0;
	while (copy_token && (copy_token->type ==  WORD || copy_token->type ==  SINGLE_QUOTES || copy_token->type ==  DOUBLE_QUOTES))
	{
		if (copy_token->value[0] == '-' && copy_token->value[1] == 'n')
		{
			i = 1;
			while (copy_token->value[i] && copy_token->value[i] == 'n')
			{
				i++;
			}
			if (copy_token->value[i] == 0)
				*n = 1;
			else
				break;
		}
		else
			break;
		copy_token = copy_token->next;
	}
	return (copy_token);
}
void	ft_echo(t_data *data, t_token *token)
{
	t_token	*copy_token;
	int	n;

	n = 0;
	copy_token = token;
	if (!copy_token->next)
	{
		printf("\n");
		return ;
	}
	copy_token = copy_token->next;
	copy_token = ft_check_n(copy_token, &n);
	// printf("## %s\n", copy_token->value);
	while (copy_token && (copy_token->type == WORD || copy_token->type == SINGLE_QUOTES || copy_token->type == DOUBLE_QUOTES))
	{
		// printf("## %s\n", copy_token->value);
		if (copy_token->value)
			printf("%s", copy_token->value);
		if (ft_condition(copy_token) == 1)
			printf(" ");
		copy_token = copy_token->next;
	}
	if (n == 0)
		printf("\n");
	data->exit_code = 0;
	return ;
}
