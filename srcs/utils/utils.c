/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:21:11 by njard             #+#    #+#             */
/*   Updated: 2025/05/16 14:09:47 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This function returns the value of the variable "name" (a string) from the environment.
char	*ft_search_value(t_env *env, char *string)
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

// This function changes the value of a variable named "name" in the environment.
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

// This function copies a string given in argument into a new char* et returns it
char	*ft_copy(char *string)
{
	int i;
	char *copied_string;

	if (!string)
		return (NULL);
	i = 0;
	while(string[i])
	{
		i++;
	}
	copied_string = malloc((i + 1) * sizeof(char));
	if (!copied_string)
		return (NULL);
	i = 0;
	while(string[i])
	{
		copied_string[i] = string[i];
		i++;
	}
	copied_string[i] = 0;
	return (copied_string);
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while(tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
