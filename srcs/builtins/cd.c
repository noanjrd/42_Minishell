/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:32:25 by njard             #+#    #+#             */
/*   Updated: 2025/05/16 14:37:12 by njard            ###   ########.fr       */
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

void ft_cd(t_data *data, t_env *env, t_token *token)
{
	char *temp;
	char *path;
	t_token *cpy_token;

	cpy_token = token;
	if (cpy_token && cpy_token->next && cpy_token->next->type == WORD)
		return(cd_error(data, token));
	temp = ft_copy(ft_search_value(env, "PWD"));
	if (!cpy_token || cpy_token->type != WORD || ft_strcmp(cpy_token->value, "~") == 0)
		path = ft_copy(ft_search_value(env, "HOME"));
	else if (ft_strcmp(cpy_token->value, "-") == 0)
	{
		path = ft_copy(ft_search_value(env, "OLDPWD"));
		if (access(path, F_OK) != 0)
			path = ft_copy(ft_search_value(env, "PWD"));
	}
	else if (cpy_token->value[0] ==  '/' && cpy_token->value[1] == 0)
		path = cd_root();
	else if (cpy_token->value[0] ==  '/')
		return(free(temp), absolute_path(env, cpy_token->value));
	else if (cpy_token && ft_strcmp(cpy_token->value, "..") != 0)
		return(go_into_specific_dr(env, ft_copy(ft_search_value(env, "PWD")), ft_join("/",cpy_token->value)));
	else if (cpy_token && ft_strcmp(cpy_token->value, "..") == 0)
		path = go_back_cd(temp);
	else
		path = token->value;
	change_value(env, "OLDPWD", temp);
	chdir(path);
	change_value(env, "PWD", path);
	data->exit_code = 0;
	return ;
}
