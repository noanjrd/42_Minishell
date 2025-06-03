/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relink_commands2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:22:15 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 15:07:36 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**allocate_new_tab(char **tab, char *value)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab && tab[i])
		i++;
	if (value)
		i++;
	new_tab = malloc((i + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	return (new_tab);
}

int	copy_existing_tab(char **new_tab, char **tab, int j)
{
	int	i;

	while (tab && tab[j])
	{
		i = 0;
		while (tab[j][i])
			i++;
		new_tab[j] = malloc((i + 1) * sizeof(char));
		if (!new_tab[j])
			return (j);
		i = 0;
		while (tab[j][i])
		{
			new_tab[j][i] = tab[j][i];
			i++;
		}
		new_tab[j++][i] = 0;
	}
	return (j);
}

int	copy_value(char **new_tab, char *value, int j)
{
	int	i;

	i = 0;
	while (value[i])
		i++;
	new_tab[j] = malloc((i + 1) * sizeof(char));
	if (!new_tab[j])
		return (j);
	i = 0;
	while (value[i])
	{
		new_tab[j][i] = value[i];
		i++;
	}
	new_tab[j++][i] = 0;
	return (j);
}

char	**ft_join_tab(char **tab, char *value, char *value_app)
{
	char	**new_tab;
	int		j;

	j = 0;
	new_tab = allocate_new_tab(tab, value);
	if (!new_tab)
		return (NULL);
	j = copy_existing_tab(new_tab, tab, j);
	if (!tab && value)
		j = copy_value(new_tab, value, j);
	j = copy_value(new_tab, value_app, j);
	new_tab[j] = NULL;
	ft_free_tab(tab);
	return (new_tab);
}

char	*ft_join_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_string;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	new_string = malloc((i + j + 2) * sizeof(char));
	if (!new_string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i++] = ' ';
	j = 0;
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = 0;
	return (free(s1), new_string);
}
