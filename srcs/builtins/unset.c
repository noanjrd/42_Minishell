/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:42:39 by njard             #+#    #+#             */
/*   Updated: 2025/03/28 13:31:18 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_env *env, char *name)
{
	t_env *cpy;
	t_env *temp;

	cpy = env;
	while (cpy)
	{
		if (cpy->next && ft_strcmp(name, cpy->next->name) == 0)
		{
			temp = cpy->next;
			if (cpy->next->next)
				cpy->next = cpy->next->next;
			else
				cpy->next = NULL;
			free(temp->name);
			free(temp->value);
			free(temp);
			return;
		}
		cpy = cpy->next;
	}
	return ;
}
