/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:25:03 by njard             #+#    #+#             */
/*   Updated: 2025/04/07 14:30:58 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *cut_builtin_echo(char *string)
{
	int i;
	int j;
	char *arg;

	i = 0;
	j = 0;
	while(string[i] == ' ' || (string[i] >= 7 && string[i] <= 13 ))
		i++;
	while(string[i] && string[i] != ' ' && !(string[i] >= 7 && string[i] <= 13 ))
		i++;
	i++;
	while(string[i + j])
		j++;
	arg = malloc((j + 1) * sizeof(char));
	if (!arg)
		return (NULL);
	j = 0;
	while(string[j + i] )
	{
		arg[j] = string[i + j];
		j++;
	}
	arg[j] = 0;
	return (arg);
}

static int	value_env(t_env *env, char *arg, int i)
{
	int j;
	char *name;
	char *value;

	j = 0;
	while (arg[i + j] && arg[i + j] != ' ')
		j++;
	name = malloc((j + 1) * sizeof(char));
	if (!name)
		return (i);
	j = 0;
	while (arg[i] && arg[i] != ' ')
	{
		name[j] = arg[i];
		i++;
		j++;
	}
	name[j] =  '\0';
	// printf("%s\n", name);
	value = ft_search_value(env, name);
	printf("%s", value);
	// free(value);
	free(name);
	// printf("%d\n", i);
	return (j);
}

void	ft_echo(t_env *env, char *commands)
{
	int i;
	int n;
	char *arg;

	arg = cut_builtin_echo(commands);
	i = 0;
	n = 0;
	// printf("%s\n", arg);

	if (arg[i] && arg[i] == '-' && arg[i+1] == 'n')
		n = 1;
	while(arg[i])
	{
		if (arg[i] != '$')
		{
			printf("%c", arg[i]);
			i++;
		}
		if (arg[i] == '$')
		{
			i++;
			i += value_env(env, arg, i);
		}
	}
	if (n == 0)
		printf("\n");
	free(arg);
	return ;
}
