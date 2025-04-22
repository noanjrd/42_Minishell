/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/04/22 11:26:50 by njard            ###   ########.fr       */
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
	while (s[i])
	{
		if (! (s[i] >= '0' && s[i] <= '9'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, t_token *token)
{
	int code_exit;
	t_token *cpy_token;

	cpy_token = token;
	if (cpy_token->next && cpy_token->next->type == WORD)
	{
		if (cpy_token->next->next && cpy_token->next->next->type == WORD)
		{
			exit_error(2);
		}
		if (check_num(cpy_token->value) == 0)
		{
			exit_error(1);
		}
		else
		{
			code_exit = ft_atoi(cpy_token->value);
		}
	}
	code_exit = data->exit_code;
	free_data(data);
	exit(code_exit);
	return ;
}
