/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:34:00 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 19:31:45 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_root(void)
{
	char	*path;

	printf("la\n");
	path = malloc(2 * sizeof(char));
	if (!path)
		return (NULL);
	path[0] = '/';
	path[1] = 0;
	return (path);
}

void	cd_error(t_data *data)
{
	write(2, " too many arguments\n", 20);
	data->exit_code = 1;
	return ;
}

static void	ft_write_error(char *path)
{
	write(2, "cd: ", 4);
	ft_putstr_fd(path, 2);
	write(2, ": No such file or directory\n", 28);
	return ;
}

void	go_into_specific_dr(t_data *data, t_env *env, char *current, char *path)
{
	char	*new_path;
	char	*temp;

	temp = getcwd(NULL, 0);
	new_path = ft_join(current, path);
	free(current);
	if (access(new_path, F_OK) == 0)
	{
		chdir(new_path);
		free(new_path);
		new_path = getcwd(NULL, 0);
		change_value(env, "PWD", new_path);
		change_value(env, "OLDPWD", temp);
		free(path);
	}
	else
	{
		path++;
		ft_write_error(path);
		path--;
		data->exit_code = 1;
		free(path);
		free(temp);
		free(new_path);
	}
}

void	absolute_path(t_env *env, char *path)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (access(path, F_OK) == 0)
	{
		chdir(path);
		change_value(env, "PWD", ft_copy(path));
		change_value(env, "OLDPWD", temp);
	}
	else
	{
		path++;
		write(2, "cd: ", 4);
		ft_putstr_fd(path, 2);
		write(2, ": No such file or directory\n", 28);
		path--;
		free(path);
		free(temp);
	}
	return ;
}
