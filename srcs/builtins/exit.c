/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/05/27 18:47:36 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	write(fd, s, i);
}

static int	check_num(char *str)
{
	int i;

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

int	ft_atoll(char *str, long long *result)
{
	size_t		i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	num = 0;
	*result = 0;
	while((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ( sign == 1 && num > ((LLONG_MAX - (str[i] - '0')) / 10)
			|| (sign == -1 && -num < (LLONG_MIN + (str[i] - '0')) / 10))
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*result = num * sign;
	return (1);
}

void free_before_exit(t_data *data)
{
	int	i;

	i = 0;
	clear_history();
	if (data->tokens)
	{
		free_token_list(data->tokens);
		data->tokens = NULL;
	}
	free_cmd(data->commands);
	if (data->env)
	{
		free_env(data->env);
		data->env = NULL;
	}
	if (data->paths_system)
	{
		while (data->paths_system[i])
		{
			free(data->paths_system[i]);
			i++;
		}
		free(data->paths_system);
	}
	free(data);
}

void	ft_exit(t_data *data, t_token *token)
{
	int			exit_code;
	t_token		*cpy_token;
	long long	ll_value;

	exit_code = 0;
	cpy_token = token->next;
	printf("exit\n");
	if (cpy_token && (cpy_token->type == WORD || cpy_token->type == DOUBLE_QUOTES || cpy_token->type == SINGLE_QUOTES))
	{
		if (!ft_atoll(cpy_token->value, &ll_value) || !check_num(cpy_token->value))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cpy_token->value, 2);
			ft_putstr_fd(": numeric argument required\n",2);
			exit_code = 2;
		}
		else if (cpy_token->next && (cpy_token->next->type == WORD || cpy_token->next->type == DOUBLE_QUOTES || cpy_token->next->type == SINGLE_QUOTES))
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit_code = 1;
			data->exit_code = exit_code;
			return ;
		}
		else
			exit_code = (int)(ll_value % 256);
	}
	free_before_exit(data);
	exit(exit_code);
}


