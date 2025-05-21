/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/05/21 18:47:57 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exit_error(int code)
{
	printf("exit\n");
	if (code == 1)
	{
		printf("exit: jdw: numeric argument required\n");
	}
	else if (code == 2)
	{
		printf("exit: too many arguments\n");
	}
	return ;
}

static int	check_num(char *s)
{
	int i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, t_token *token)
{
	int		code_exit;
	t_token	*cpy_token;

	code_exit = 0;
	cpy_token = token;
	if (cpy_token->next && cpy_token->next->type == WORD)
	{
		if (check_num(cpy_token->next->value) == 0)
		{
			printf("exit\n");
			code_exit = ft_atoi(cpy_token->next->value);
		}
		// if (cpy_token->next->next && cpy_token->next->next->type == WORD)
		// {
		// 	exit_error(2);
		// 	data->exit_code = 1;
		// 	return ;
		// }
		// else
		// {
		// 	code_exit = ft_atoi(cpy_token->value);
		// }
	}
	// printf("exit\n");
	free_token_list(token);
	free_data(data);
	exit(code_exit);
	return ;
}


// ce qui est deja fait