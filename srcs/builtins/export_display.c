/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:57:03 by njard             #+#    #+#             */
/*   Updated: 2025/04/07 10:17:51 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void sort_env(t_env *env)
{
	t_env	*current;
	t_env	*min;

	min = NULL;
	current = env;
	while (current)
	{
		if (current->displayed == 0)
		{
			if (!min || ft_strcmp(current->name, min->name) < 0)
				min = current;
		}
		if (!current->next)
			break;
		current = current->next;
	}
	if (min)
	{
		min->displayed = 1;
		if (min->value)
			printf("declare -x %s=%s\n", min->name, min->value);
		else
			printf("declare -x %s\n", min->name);
		display_export(env);
	}
}

void	display_export(t_env *env)
{
	t_env *cpy;

	cpy = env;
	sort_env(env);
	while(cpy)
	{
		cpy->displayed = 0;
		cpy = cpy->next;
	}
	return ;
}
