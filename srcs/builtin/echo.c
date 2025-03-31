/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:25:03 by njard             #+#    #+#             */
/*   Updated: 2025/03/31 12:21:34 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	value_env(t_env *env, char *arg, int i)
{
	int j;
	char *name;
	char *value;

	j = 0;
	while (arg[i + j] && arg[i + j] != ' ')
		j++;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (0);
	j = 0;
	while (arg[i] && arg[i] != ' ')
	{
		name[j] = arg[i];
		i++;
	}
	name[j] = 0;
	value = search_value(env, name);
	printf("%s", value);
	free(value);
	free(name);
	return (i);
}

void	ft_echo(t_env *env, char *arg)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] != '$')
		{
			printf("%c", arg[i]);
		}
		if (arg[i] == '$')
		{
			i = value_env(env, arg, i);
		}
		i++;
	}
	printf("\n");
	return ;
}
