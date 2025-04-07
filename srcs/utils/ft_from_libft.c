/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_from_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:28:00 by njard             #+#    #+#             */
/*   Updated: 2025/04/07 12:56:26 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(char *string)
{
	int i;

	i = 0;
	while(string[i])
	{
		i++;
	}
	return (i);
}

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

int	ft_strstr(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while(s1[i])
	{
		if (s1[i] == s2[0])
		{
			j = 1;
			while (s2[j])
			{
				if (s2[j] != s1[i + j])
					break;
				if (s2[j + 1] == '\0')
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}
