/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:35 by njard             #+#    #+#             */
/*   Updated: 2025/05/27 11:49:26 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// le shell va dabord check si ce sont des chiffres et sil y a bien un seul signe
// ensuite essaye de le convertir en long long si echec erreur et code exit 255
// numeric argument required

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

// doit etre compris dans un long long donc ft_atoll

// int	ft_atoll(char *str, long long *result)
// {
// 	size_t		i;
// 	int			sign;
// 	long long	num;

// 	i = 0;
// 	sign = 1;
// 	*result = 0;
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
// 		if ( sign == 1 && result > ((LLONG_MAX - (str[i] - '0')) / 10))
// 			return (0);
// 		if( sign == -1 && result < (LLONG_MIN + (str[i] - '0') / 10))
// 			return (0);
// 		num = num * 10 + sign * (str[i] - '0');
// 		i++;
// 	}
// 	if (str[i] != '\0');
// 		return (0);
// 	*result = num;
// 	return (0);
// }

void	ft_exit(t_data *data, t_token *token)
{
	int		code_exit;
	t_token	*cpy_token;

	code_exit = 0;
	cpy_token = token;
	if (cpy_token->next && (cpy_token->next->type == WORD || cpy_token->next->type == DOUBLE_QUOTES || cpy_token->next->type == SINGLE_QUOTES))
	{
		if (!check_num(cpy_token->next->value))
		{
			// ajouter !ft_atoll
			printf("exit\n");
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cpy_token->next->value, 2);
			ft_putstr_fd(": numeric argument required\n",2);
			code_exit = 2;
		}
		else if (check_num(cpy_token->next->value) == 1)
		{
			printf("exit\n");
			// free_token_list(token);
			// free_data(data);
			code_exit = ft_atoi(cpy_token->next->value);
		}
		else
		{

		}
	}
	// printf("exit\n");
	free_token_list(token);
	free_data(data);
	exit(code_exit);
	return ;
}


// int	ft_exit(t_cmd *cmd, t_ms *minishell, char **args)
// {
// 	t_token		*token;
// 	int			exit_status;
// 	long long	numeric_value;
// 	int			res;

// 	exit_status = 0;
// 	token = cmd->token->next;
// 	ft_putstr_fd("exit\n", 1);
// 	if (token)
// 	{
// 		res = ft_exit_error(token, minishell, &numeric_value, args);
// 		if (res == 1)
// 			return (1);
// 		if (res == 2)
// 			exit_status = 2;
// 		else
// 			exit_status = (unsigned char)numeric_value;
// 	}
// 	exit_clean(minishell, args);
// 	// minishell->status = exit_status;
// 	exit(exit_status);
// }

// int	ft_exit_error(t_token *token, t_ms *ms, long long *numeric_value, char ** args)
// {
// 	if (!db_sign(token->value) || !ft_atoll(token->value, numeric_value))
// 	{
// 		ft_putstr_fd("minishell: exit: ", 2);
// 		ft_putstr_fd(token->value, 2);
// 		ft_putstr_fd(": numeric argument required\n", 2);
// 		ms->status = 2;
// 		return (2);
// 		exit_clean(ms, args);
// 		exit(ms->status);
// 	}
// 	else if (token->next)
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		ms->status = 1;
// 		return (1);
// 	}
// 	return (0);
// }



// void	exit_clean(t_ms *ms, char **args)
// {
// 	free(ms->pwd);
// 	free(ms->current_prompt);
// 	free_env(ms);
// 	free_array(ms->envp);
// 	free_array(args);
// 	free_cmd_list(ms->cmd_list);
// 	free(ms->exec);
// 	free(ms);
// }

// int	check_overflow(long long result, int digit, int sign)
// {
// 	if (sign == 1 && (result > (LLONG_MAX - digit) / 10))
// 		return (0);
// 	if (sign == -1 && (-result < (LLONG_MIN + digit) / 10))
// 		return (0);
// 	return (1);
// }
