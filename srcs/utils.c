/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:21:11 by njard             #+#    #+#             */
/*   Updated: 2025/03/31 12:22:57 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// This function returns 0 if s1 and s2 are identical, or the difference between them if they are not.
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

char *ft_join(char *s1, char *s2)
{
	int i;
	int j;
	char *new_string;

	i = 0;
	j = 0;
	while(s1[i])
		i++;
	while(s2[j])
		j++;
	new_string = malloc((i + j + 1) * sizeof(char));
	if (!new_string)
		return(NULL);
	i = 0;
	j = 0;
	while(s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = 0;
	return(new_string);
}

// This function returns the value of the variable "name" (a string) from the environment.
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
