/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:42:48 by njard             #+#    #+#             */
/*   Updated: 2025/05/09 15:30:09 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*builtin_second(t_data *data, t_token *token, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		ft_export(data->env, token);
		data->builtin_found = 1;
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		ft_cd(data, data->env, token->next);
		data->builtin_found = 1;
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		ft_pwd(data->env);
		data->builtin_found = 1;
		return (free(arg), token->next);
	}
	return (token->next);
}

t_token	*builtin(t_data *data, t_token *token, char *commands)
{
	char *arg;
	
	arg = NULL;

	if (ft_strcmp(commands, "echo") == 0)
	{
		ft_echo(data, data->env, token);
		data->builtin_found = 1;
		return (free(arg), update_echo_struct(token));
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		ft_unset(data->env, token);
		data->builtin_found = 1;
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "env") == 0)
	{
		display_env(data->env);
		data->builtin_found = 1;
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "exit") == 0)
	{
		ft_exit(data, token);
	}
	return(builtin_second(data, token, commands));
}

t_token	*builtin_second_check(t_data *data, t_token *token, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		data->builtin_found = 1;
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		data->builtin_found = 1;
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		data->builtin_found = 1;
	}
	return (token->next);
}

t_token	*builtin_check(t_data *data, t_token *token, char *commands)
{
	char *arg;
	
	arg = NULL;

	if (ft_strcmp(commands, "echo") == 0)
	{
		data->builtin_found = 1;
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		data->builtin_found = 1;
	}
	if (ft_strcmp(commands, "env") == 0)
	{
		data->builtin_found = 1;
	}
	if (ft_strcmp(commands, "exit") == 0)
	{
		ft_exit(data, token);
	}
	return(builtin_second(data, token, commands));
}
