/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:32:25 by njard             #+#    #+#             */
/*   Updated: 2025/05/14 12:18:00 by naankour         ###   ########.fr       */
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
	new_path = malloc((i + 2) * sizeof(char));
	if (!new_path)
		return (NULL);
	while (j < i)
	{
		new_path[j] = path[j];
		j++;
	}
	if (i == 0)
	{
		new_path[0] = '/';
		j++;
	}
	new_path[j] = 0;
	return (new_path);
}

static void go_into_specific_dr(t_env *env, char *current, char *path)
{
	char *new_path;
	char *temp;

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
		printf("no such file or directory: %s\n", path);
		path--;
		free(path);
		free(new_path);
	}
	return ;
}

static void absolute_path(t_env *env, char *path)
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
		// path++;
		printf("no such file or directory: %s\n", path);
		// path--;
		free(path);
		free(temp);
	}
	return ;
}

// void ft_cd(t_env *env, t_token *token)
// {
// 	char *temp;
// 	char *path;
// 	t_token

// 	temp = getcwd(NULL, 0);
// 	change_value(env, "OLDPWD", temp);
// 	if (!arg || arg[0] == '\0' || !arg[0])
// 	{
// 		path = ft_copy(ft_search_value(env, "HOME"));
// 	}
// 	else if (arg && ft_strcmp(arg, "..") != 0)
// 	{
// 		return(go_into_specific_dr(env, ft_copy(ft_search_value(env, "OLDPWD")), ft_join("/",arg)));
// 	}
// 	else if (arg && ft_strcmp(arg, "..") == 0)
// 	{
// 		path = go_back_cd(temp);
// 	}
// 	else
// 		path = arg;
// 	chdir(path);
// 	change_value(env, "PWD", path);
// 	return ;
// }

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
	printf("cd: too many arguments\n");
	data->exit_code = 1;
	return ;
}

void ft_cd(t_data *data, t_env *env, t_token *token)
{
	char *temp;
	char *path;
	t_token *cpy_token;

	cpy_token = token;
	if (cpy_token && cpy_token->next && cpy_token->next->type == WORD)
	{
		return(cd_error(data, token));
	}
	temp = ft_copy(ft_search_value(env, "PWD"));
	if (!cpy_token || cpy_token->type != WORD || ft_strcmp(cpy_token->value, "~") == 0)
	{
		// printf("home\n");
		path = ft_copy(ft_search_value(env, "HOME"));
		// printf("!!!!%s, %s\n", path, ft_search_value(env, "PWD"));
	}
	else if (ft_strcmp(cpy_token->value, "-") == 0)
	{
		path = ft_copy(ft_search_value(env, "OLDPWD"));
		if (access(path, F_OK) != 0)
			path = ft_copy(ft_search_value(env, "PWD"));
	}
	else if (cpy_token->value[0] ==  '/' && cpy_token->value[1] == 0)
		path = cd_root();
	else if (cpy_token->value[0] ==  '/')
	{
		return(free(temp), absolute_path(env, cpy_token->value));
	}
	else if (cpy_token && ft_strcmp(cpy_token->value, "..") != 0)
		return(go_into_specific_dr(env, ft_copy(ft_search_value(env, "PWD")), ft_join("/",cpy_token->value)));
	else if (cpy_token && ft_strcmp(cpy_token->value, "..") == 0)
	{
		// printf("..\n");
		path = go_back_cd(temp);
	}
	else
		path = token->value;
	change_value(env, "OLDPWD", temp);
	chdir(path);
	change_value(env, "PWD", path);
	// printf("%s, %s\n", path, ft_search_value(env, "PWD"));
	data->exit_code = 0;
	return ;
}
