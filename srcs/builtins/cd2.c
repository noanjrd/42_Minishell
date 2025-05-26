/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:34:00 by njard             #+#    #+#             */
/*   Updated: 2025/05/26 11:51:20 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *cd_root(void)
{
	char *path;

	path = malloc(2 * sizeof(char));
	if (!path)
		return (NULL);
	path[0] = '/';
	path[1] = 0;
	return (path);
}

void	cd_error(t_data *data, t_token *token)
{
	write(2," too many arguments\n",20);
	data->exit_code = 1;
	return ;
}

void	ft_putstr_error(char *str, int space)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2,&str[i],1);
		i++;
	}
	if (space == 1)
		write(2,"\n",1);
	return ;
}

void go_into_specific_dr(t_data *data, t_env *env, char *current, char *path)
{
	char *new_path;
	char *temp;

	// printf("yeah\n");
	temp = getcwd(NULL, 0);
	new_path = ft_join(current, path);
	free(current);
	if (access(new_path, F_OK) == 0)
	{
		chdir(new_path);
		change_value(env, "PWD", new_path);
		change_value(env, "OLDPWD", temp);
		free(path);
		return ;
	}
	else
	{
		path++;
		write(2,"cd: ",4);
		ft_putstr_error(path, 0);
		write(2,": No such file or directory\n",28);
		path--;
		data->exit_code = 1;
		free(path);
		free(new_path);
	}
	return ;
}

void absolute_path(t_env *env, char *path)
{
	char *temp;

	temp = getcwd(NULL, 0);
	// printf("%s\n", path);
	if (access(path, F_OK) == 0)
	{
		chdir(path);
		change_value(env, "PWD", path);
		change_value(env, "OLDPWD", temp);
		return ;
	}
	else
	{
		path++;
		write(2,"cd: ",4);
		ft_putstr_error(path, 0);
		write(2,": No such file or directory\n",28);
		path--;
		free(path);
		free(temp);
	}
	return ;
}
