/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:46 by njard             #+#    #+#             */
/*   Updated: 2025/04/07 13:14:34 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **cut_system_path_next(char **path, char *value)
{
	int i;
	int j;
	int z;

	i = 0;
	z = 0;
	j = 0;
	while(value[i])
	{
		path[z][j] = value[i];
		if (value[i] == ':' || value[i + 1] == '\0')
		{
			path[z][j] = '/';
			path[z][j + 1] = '\0';
			j = -1;
			z++;
		}
		j++;
		i++;
	}
	return (path);
}

static char	**cut_system_path(char *value, char **path)
{
	int i;
	int j;
	int z;

	j = 0;
	i = 0;
	z = 0;
	while(value[i])
	{
		if (value[i + 1] == ':' || value[i + 1] == 0)
		{
			path[z] = malloc((i - j + 3) * sizeof(char)); //Regarder ici si leak un jour
			j = i + 1;
			z++;
		}
		i++;
	}
	path = cut_system_path_next(path, value);
	path[z] = NULL;
	return (path);
}

void	initalising_path(t_data *data)
{
	t_env *copy;
	char **path;
	int i;
	int j;

	copy = data->env;
	while(copy)
	{
		if (ft_strcmp(copy->name, "PATH") == 0)
			break;
		copy = copy->next;
	}
	i = 0;
	j =0;
	while (copy->value[i])
	{
		if (copy->value[i] == ':' || copy->value[i + 1] == '\0')
			j++;
		i++;
	}
	path = malloc((j + 1) * sizeof(char *));
	if (!path)
		return ;
	path = cut_system_path(copy->value, path);
	data->paths_system = path;
}

int	check_path_exist(t_data *data, char *command)
{
	char *entire_path;
	int i;

	i = 0;
	if (command[0] == 0)
		return (0);
	while (data->paths_system[i])
	{
		entire_path = ft_join(data->paths_system[i], command);
		// printf("%s\n", entire_path);
		if (access(entire_path, F_OK) == 0)
		{
			free(entire_path);
			return (1);
		}
		free(entire_path);
		i++;
	}
	return 0;
}
