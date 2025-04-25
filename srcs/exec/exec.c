/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/04/25 11:31:05 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*cut_builtin(char *string)
// {
// 	int i;
// 	int j;
// 	char *arg;

// 	i = 0;
// 	j = 0;
// 	while(string[i] == ' ' || (string[i] >= 7 && string[i] <= 13 ))
// 		i++;
// 	while(string[i] && string[i] != ' ')
// 		i++;
// 	if (string[i] == ' ')
// 		i++;
// 	while(string[i + j] && string[i + j] != ' ' && !(string[i + j] >= 7 && string[i + j] <= 13))
// 		j++;
// 	arg = malloc((j + 1) * sizeof(char));
// 	if (!arg)
// 		return (NULL);
// 	j = 0;
// 	while(string[j + i] && string[i + j] != ' ' && !(string[i + j] >= 7 && string[i + j] <= 13 ))
// 	{
// 		arg[j] = string[i + j];
// 		j++;
// 	}
// 	arg[j] = 0;
// 	return (arg);
// }

int	builtin_second(t_data *data, t_token *token, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		ft_export(data->env, token);
		return (free(arg), 1);
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		ft_cd(data->env, token->next);
		return (free(arg), 1);
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		ft_pwd(data->env);
		return (free(arg), 1);
	}
	return (0);
}

int	builtin(t_data *data, t_token *token, char *commands)
{
	char *arg;
	
	arg = NULL;

	if (ft_strcmp(commands, "echo") == 0)
	{
		ft_echo(data, data->env, token);
		return (free(arg), 1);
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		ft_unset(data->env, token);
		return (free(arg), 1);
	}
	if (ft_strcmp(commands, "env") == 0)
	{
		display_env(data->env);
		return (free(arg), 1);
	}
	if (ft_strcmp(commands, "exit") == 0)
	{
		ft_exit(data, token);
	}
	return(builtin_second(data, token, commands));
}

void	exec(t_data *data)
{
	int i;

	i = 0;
	t_token *cpy_token;

	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
		{
			here_doc(cpy_token->next->value, data);
		}
		cpy_token = cpy_token->next;
	}
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->type == REDIRECT_IN)
		{
			here_doc(cpy_token->next->value, data);
		}
		cpy_token = cpy_token->next;
	}
	cpy_token = data->tokens;
	while (cpy_token)
	{
		if (cpy_token->type == WORD)
		{
			builtin(data, cpy_token, cpy_token->value);
		}
		if (cpy_token->type == HERE_DOC)
		{
			here_doc(cpy_token->next->value, data);
		}
		cpy_token = cpy_token->next;
	}
	// if (builtin(data, data->env, instru) == 1)
	// {
	// 	// printf("builtin\n");
	// 	return ;
	// }
	// // initalising_path(data);
	// if (check_path_exist(data, instru) == 1)
	// {
	// 	// printf("other\n");
	// 	// printf("wsh\n");
	// 	return;
	// }
	// if (ft_strstr(instru, "<<"))
	// {
	// 	// printf("here\n");
	// 	here_doc(instru);
	// 	// printf("wsh\n");
	// 	return;
	// }
	// printf("%s\n",instru);
	// printf("%d\n",ft_strstr(instru, "export"));
	return ;
}
