/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:32:25 by njard             #+#    #+#             */
/*   Updated: 2025/04/04 12:31:13 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *go_back_cd(char *path)
{
	char *new_path;
	int i;
	int j;

	j = 0;
	i = 0;
	while(path[i])
		i++;
	while(path[i] != '/')
		i--;
	new_path = malloc((i + 1) * sizeof(char));
	if (!new_path)
		return (NULL);
	while (j < i)
	{
		new_path[j] = path[j];
		j++;
	}
	new_path[j] = 0;
	return (new_path);
}

static void go_into_specific_dr(t_env *env, char *current, char *path)
{
	char *new_path;

	new_path = ft_join(current, path);
	free(current);
	if (access(new_path, F_OK) == 0)
	{
		chdir(new_path);
		change_value(env, "PWD", new_path);
		free(path);
		return ;
	}
	else
	{
		path++;
		printf("no such file or directory: %s\n", path);
		path--;
		free(path);
		free(new_path);
	}
	return ;
}

void ft_cd(t_env *env, char *arg)
{
	char *temp;
	char *path;

	temp = getcwd(NULL, 0);
	change_value(env, "OLDPWD", temp);
	if (!arg || arg[0] == '\0' || !arg[0])
	{
		path = ft_copy(ft_search_value(env, "HOME"));
	}
	else if (arg && ft_strcmp(arg, "..") != 0)
	{
		return(go_into_specific_dr(env, ft_copy(ft_search_value(env, "OLDPWD")), ft_join("/",arg)));
	}
	else if (arg && ft_strcmp(arg, "..") == 0)
	{
		path = go_back_cd(temp);
	}
	else
		path = arg;
	chdir(path);
	change_value(env, "PWD", path);
	return ;
}
