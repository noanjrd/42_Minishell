/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:21:11 by njard             #+#    #+#             */
/*   Updated: 2025/04/02 14:51:00 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// This function frees the memory allocated for the environment.
void	free_env(t_env *env)
{
	t_env *temp;

	temp = env;
	while(temp)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
	return ;
}

// This function returns the value of the variable "name" (a string) from the environment.
char	*ft_search_value(t_env *env, char *string)
{
	t_env *copy;

	copy = env;
	// printf("test\n");
	while(copy)
	{
		// printf("%s : %s\n", copy->name, string);
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

//This function displays the environment.
void	display_env(t_env *env)
{
	t_env *head;

	head = env;
	while(head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	return ;
}
