/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:34:00 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 16:04:39 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(t_data *data)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	data->exit_code = 1;
	return ;
}

static void	ft_error_no_file(t_data *data, char *path,
								char *new_path, char *temp)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Not a directory\n", 2);
	data->exit_code = 1;
	free(path);
	free(temp);
	free(new_path);
	return ;
}

static void	ft_error_no_folder(t_data *data, char *path,
								char *new_path, char *temp)
{
	struct stat	sb;

	path++;
	stat(path, &sb);
	if (S_ISREG(sb.st_mode))
	{
		path--;
		return (ft_error_no_file(data, path, new_path, temp));
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	path--;
	data->exit_code = 1;
	free(path);
	free(temp);
	free(new_path);
	return ;
}

void	go_into_specific_dr(t_data *data, t_env *env, char *current, char *path)
{
	char		*new_path;
	char		*temp;
	struct stat	sb;

	stat(path, &sb);
	temp = getcwd(NULL, 0);
	new_path = ft_join(current, path);
	free(current);
	if (access(new_path, X_OK) == 0)
	{
		if (S_ISREG(sb.st_mode))
		{
			return (ft_error_no_file(data, path, new_path, temp));
		}
		chdir(new_path);
		free(new_path);
		new_path = getcwd(NULL, 0);
		ft_change_value_fd(env, "PWD", new_path);
		ft_change_value_fd(env, "OLDPWD", temp);
		free(path);
	}
	else
		ft_error_no_folder(data, path, new_path, temp);
}

void	absolute_path(t_env *env, char *path)
{
	char	*temp;
	char	*temp2;

	temp = getcwd(NULL, 0);
	if (access(path, F_OK) == 0)
	{
		chdir(path);
		temp2 = getcwd(NULL, 0);
		ft_change_value_fd(env, "PWD", temp2);
		ft_change_value_fd(env, "OLDPWD", temp);
	}
	else
	{
		path++;
		ft_putstr_fd("minishell: ", 2);
		write(2, "cd: ", 4);
		ft_putstr_fd(path, 2);
		write(2, ": No such file or directory\n", 28);
		path--;
		free(temp);
	}
	return ;
}
