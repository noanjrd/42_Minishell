/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:21:11 by njard             #+#    #+#             */
/*   Updated: 2025/03/28 15:24:23 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*search_value(t_env *env, char *string)
{
	t_env *copy;

	copy = env;
	while(copy)
	{
		if (ft_strcmp(string, copy->name) == 0)
			return (copy->value);
		copy = copy->next;
	}
	return (NULL);
}

void	change_value(t_env *env, char *name, char *value)
{
	t_env *copy;

	copy = env;
	while(copy)
	{
		if (ft_strcmp(name, copy->name) == 0)
		{
			free(copy->value);
			copy->value = value;
			return ;
		}
		copy = copy->next;
	}
	return ;
}
