/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:32:25 by njard             #+#    #+#             */
/*   Updated: 2025/03/31 12:21:41 by njard            ###   ########.fr       */
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

void ft_cd(t_env *env, char *arg)
{
	char *temp;
	char *path;

	temp = getcwd(NULL, 0);
	change_value(env, "OLDPWD", temp);
	free(temp);
	if (!arg || arg[0] == '\0' || !arg[0])
	{
		path = search_value(env, "HOME");
	}
	if (arg && ft_strcmp(arg, "..") == 0)
	{
		path = go_back_cd(temp);
	}
	else
		path = arg;
	chdir(path);
	change_value(env, "PWD", path);
	return ;
}
