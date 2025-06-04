/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 16:17:46 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_putstr_error(t_token *token)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	is_valid_token_type(t_token *token)
{
	if (!token)
		return (0);
	if ((token->type == WORD || token->type == DOUBLE_QUOTES
			|| token->type == SINGLE_QUOTES))
		return (1);
	return (0);
}

static int	parse_exit_code(t_token *token, t_data *data)
{
	t_token		*cpy_token;
	long long	ll_value;
	int			exit_code;

	exit_code = 0;
	cpy_token = token->next;
	if (is_valid_token_type(cpy_token) == 1)
	{
		if (!ft_atoll(cpy_token->value, &ll_value)
			|| !check_num(cpy_token->value))
		{
			ft_putstr_error(cpy_token);
			exit_code = 2;
		}
		else if (has_too_many_args(cpy_token) == 1)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->exit_code = 1;
			return (-1);
		}
		else
			exit_code = (unsigned char)(ll_value);
	}
	return (exit_code);
}

static int	has_pipe(t_token *token)
{
	t_token	*cpy_token;

	cpy_token = token;
	while (cpy_token)
	{
		if (cpy_token->type == PIPE)
			return (1);
		cpy_token = cpy_token->next;
	}
	return (0);
}

void	ft_exit(t_data *data, t_token *token)
{
	int	exit_code;

	if (has_pipe(data->tokens) == 1)
		return ;
	printf("exit\n");
	exit_code = parse_exit_code(token, data);
	if (exit_code == -1)
		return ;
	free_and_exit(data, exit_code);
}
