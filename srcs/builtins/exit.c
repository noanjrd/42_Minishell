/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/05/24 14:26:52 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// le shell va dabord check si ce sont des chiffres
// ensuite essaye de le convertir en long long si echec erreur et code exit 255
// numeric argument required
static int	check_num(char *s)
{
	int i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
	i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		return (0);
		i++;
	}
	return (1);
}

// doit etre compris dans un long long donc ft_atoll

// int	ft_atoll(char *str, long long *result)
// {
// 	size_t		i;
// 	int			sign;
// 	long long	result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		if ( sign == 1 && result > ((LLONG_MAX - (str[i] - '0'))/ 10))
// 			return (0);
// 		if( sign == -1 && result > )
// 	}

// }
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

void	ft_exit(t_data *data, t_token *token)
{
	int		code_exit;
	t_token	*cpy_token;

	code_exit = 0;
	cpy_token = token;
	if (cpy_token->next && cpy_token->next->type == WORD)
	{
		if (check_num(cpy_token->next->value) == 1)
		{
			exit_error(1);
			code_exit = 2;
			free_token_list(token);
			free_data(data);
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


// int	check_overflow(long long result, int digit, int sign)
// {
// 	if (sign == 1 && (result > (LLONG_MAX - digit) / 10))
// 		return (0);
// 	if (sign == -1 && (-result < (LLONG_MIN + digit) / 10))
// 		return (0);
// 	return (1);
// }

// int	ft_atoll(const char *str, long long *out)
// {
// 	int			i = 0;
// 	int			sign = 1;
// 	long long	result = 0;

// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			return (0);
// 		int digit = str[i] - '0';
// 		if (!check_overflow(result, digit, sign))
// 			return (0);
// 		result = result * 10 + digit;
// 		i++;
// 	}
// 	*out = result * sign;
// 	return (1);
// }