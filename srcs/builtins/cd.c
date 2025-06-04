/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: njard <njard@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/28 13:32:25 by njard			 #+#	#+#			 */
/*   Updated: 2025/05/28 12:07:31 by njard			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_condition_one(t_token *token)
{
	if (token->type == WORD
		|| token->type == DOUBLE_QUOTES
		|| token->type == SINGLE_QUOTES)
	{
		return (1);
	}
	return (0);
}

static char	*go_back_cd(char *path)
{
	char	*new_path;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (path[i])
		i++;
	while (path[i] != '/')
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

char	*resolve_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = ft_copy(ft_search_value(env, "OLDPWD"));
	if (access(oldpwd, F_OK) != 0)
		return (ft_copy(ft_search_value(env, "PWD")));
	return (oldpwd);
}

char	*resolve_cd_path(t_data *data, t_env *env, t_token *token, char *temp)
{
	if (token && token->next && ft_condition_one(token->next) == 1)
		return (cd_error(data), NULL);
	if (!token || ft_condition_one(token) == 0
		|| ft_strcmp(token->value, "~") == 0)
	{
		if (ft_search_value(env, "HOME"))
			return (ft_copy(ft_search_value(env, "HOME")));
		else
			return (ft_putstr_fd("minishell: cd: HOME no set\n", 2), NULL);
	}
	if (ft_strcmp(token->value, "-") == 0)
		return (resolve_oldpwd(env));
	if (token->value[0] == '/' && token->value[1] == '\0')
		return (cd_root());
	if (token->value[0] == '/')
		return (absolute_path(env, token->value), NULL);
	if (ft_strcmp(token->value, "..") == 0)
		return (go_back_cd(temp));
	return (go_into_specific_dr(data, env,
			ft_copy(temp),
			ft_join("/", token->value)), NULL);
}

void	ft_cd(t_data *data, t_env *env, t_token *token)
{
	char	*temp;
	char	*path;

	temp = getcwd(NULL, 0);
	path = resolve_cd_path(data, env, token, temp);
	if (!path)
		return (free(temp));
	if (access(path, F_OK) != 0)
	{
		free(temp);
		free(path);
		ft_putstr_fd("chdir: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: No ", 2);
		ft_putstr_fd("such file or directory\n", 2);
		data->exit_code = 1;
		return ;
	}
	ft_change_value_fd(env, "OLDPWD", temp);
	chdir(path);
	ft_change_value_fd(env, "PWD", path);
	data->exit_code = 0;
}
