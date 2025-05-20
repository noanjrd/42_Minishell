/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:42:48 by njard             #+#    #+#             */
/*   Updated: 2025/05/17 18:21:06 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*builtin_second(t_data *data, t_token *token, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		ft_export(data, data->env, token);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		// printf("its cdddd\n");
		ft_cd(data, data->env, token->next);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		ft_pwd(data->env);
		return (free(arg), token->next);
	}
	return (token->next);
}

t_token	*builtin(t_data *data, t_token *token, char *commands)
{
	char *arg;

	arg = NULL;

	// printf("builtin???\n");
	if (ft_strcmp(commands, "echo") == 0)
	{
		ft_echo(data, data->env, token);
		return (free(arg), update_echo_struct(token));
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		ft_unset(data->env, token);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "env") == 0)
	{
		display_env(data->env);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "exit") == 0)
	{
		ft_exit(data, token);
	}
	return(builtin_second(data, token, commands));
}

void	go_to_right_builtin(t_data *data, int i)
{
	t_token *cpy_token;

	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->index == i)
			break;
		cpy_token = cpy_token->next;
	}
	builtin(data, cpy_token, cpy_token->value);
	return ;
}

int	builtin_second_check(t_data *data, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		return (2);
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		return (1);
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		return (1);
	}
	return (0);
}

int	builtin_check(t_data *data, char *commands)
{
	char *arg;

	arg = NULL;

	// printf("buiiii '%s'\n", commands);
	if (ft_strcmp(commands, "echo") == 0)
	{
		// printf("echoi\n");
		return (1);
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		return (1);
	}
	if (ft_strcmp(commands, "env") == 0)
	{
		return (1);
	}
	if (ft_strcmp(commands, "exit") == 0)
	{
		return (1);
	}
	return(builtin_second_check(data, commands));
}
