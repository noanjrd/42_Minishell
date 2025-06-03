/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/06/02 18:30:34 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_putstr_error(t_token *token)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	has_too_many_args(t_token *token)
{
	if (!token)
		return (0);
	if (token->next && (token->next->type == WORD
			|| token->next->type == DOUBLE_QUOTES
			|| token->next->type == SINGLE_QUOTES))
		return (1);
	return (0);
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

void	ft_exit(t_data *data, t_token *token)
{
	int			exit_code;
	t_token		*cpy_token;
	long long	ll_value;

	exit_code = 0;
	cpy_token = token->next;
	printf("exit\n");
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
			return ;
		}
		else
			exit_code = (unsigned char)(ll_value);
	}
	free_and_exit(data, exit_code);
}
