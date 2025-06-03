/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:42:48 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 18:24:08 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*builtin_second(t_data *data, t_token *token, char *commands)
{
	char	*arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		ft_export(data, data->env, token);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		ft_cd(data, data->env, token->next);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		ft_pwd();
		return (free(arg), token->next);
	}
	return (token->next);
}

t_token	*builtin(t_data *data, t_token *token, char *commands)
{
	char	*arg;

	arg = NULL;
	if (ft_strcmp(commands, "echo") == 0)
	{
		ft_echo(data, token);
		return (free(arg), update_echo_struct(token));
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		ft_unset(data, token);
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
	return (builtin_second(data, token, commands));
}

void	go_to_right_builtin(t_data *data, int i)
{
	t_token	*cpy_token;

	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->index == i)
			break ;
		cpy_token = cpy_token->next;
	}
	builtin(data, cpy_token, cpy_token->value);
	return ;
}

int	builtin_second_check(t_cmd *cmd)
{
	if (ft_strcmp(cmd->value, "export") == 0
		|| (cmd->next && ft_strstr(cmd->value, "export") == 1))
	{
		return (1);
	}
	if (ft_strstr(cmd->value, "export") == 1)
		return (2);
	if (ft_strcmp(cmd->tab[0], "cd") == 0)
	{
		return (2);
	}
	if (ft_strcmp(cmd->tab[0], "pwd") == 0)
	{
		return (1);
	}
	return (0);
}

int	builtin_check(t_cmd *cmd)
{
	if (ft_strcmp(cmd->tab[0], "echo") == 0)
	{
		return (1);
	}
	if (ft_strcmp(cmd->tab[0], "unset") == 0)
	{
		return (2);
	}
	if (ft_strcmp(cmd->tab[0], "env") == 0)
	{
		return (1);
	}
	if (ft_strcmp(cmd->tab[0], "exit") == 0)
	{
		return (2);
	}
	return (builtin_second_check(cmd));
}
