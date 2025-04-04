/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/04/04 12:36:23 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cut_builtin(char *string)
{
	int i;
	int j;
	char *arg;

	i = 0;
	j = 0;
	while(string[i] == ' ' || (string[i] >= 7 && string[i] <= 13 ))
		i++;
	while(string[i] && string[i] != ' ')
		i++;
	if (string[i] == ' ')
		i++;
	while(string[i + j] && string[i + j] != ' ' && !(string[i + j] >= 7 && string[i + j] <= 13))
		j++;
	arg = malloc((j + 1) * sizeof(char));
	if (!arg)
		return (NULL);
	j = 0;
	while(string[j + i] && string[i + j] != ' ' && !(string[i + j] >= 7 && string[i + j] <= 13 ))
	{
		arg[j] = string[i + j];
		j++;
	}
	arg[j] = 0;
	return (arg);
}

int	builtin_second(t_env *env, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strstr(commands, "export") == 1)
	{
		ft_export(env, commands);
		return (free(arg), 1);
	}
	if (ft_strstr(commands, "cd") == 1)
	{
		arg = cut_builtin(commands);
		// printf("| %s| \n", arg);
		ft_cd(env, arg);
		return (free(arg), 1);
	}
	return (0);
}

int	builtin(t_data *data, t_env *env, char *commands)
{
	char *arg;
	
	arg = NULL;
	if (ft_strstr(commands, "echo") == 1)
	{
		ft_echo(env, commands);
		return (free(arg), 1);
	}
	if (ft_strstr(commands, "unset") == 1)
	{
		arg = cut_builtin(commands);
		ft_unset(env, arg);
		return (free(arg), 1);
	}
	if (ft_strstr(commands, "env") == 1)
	{
		display_env(env);
		return (free(arg), 1);
	}
	if (ft_strstr(commands, "exit") == 1)
	{
		ft_exit(data);
	}
	return(builtin_second(env, commands));
}

void	exec(t_data *data, char *instru)
{
	int i;

	i = 0;
	if (builtin(data, data->env, instru) == 1)
	{
		// printf("builtin\n");
		return ;
	}
	// initalising_path(data);
	if (check_path_exist(data, instru) == 1)
	{
		// printf("other\n");
		// printf("wsh\n");
		return;
	}
	
	// printf("%s\n",instru);
	// printf("%d\n",ft_strstr(instru, "export"));
	return ;
}
