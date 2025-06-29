/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:42:39 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 11:13:07 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove(t_env *env, char *name)
{
	t_env	*cpy;
	t_env	*temp;

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
			return ;
		}
		cpy = cpy->next;
	}
	return ;
}

void	ft_unset(t_data *data, t_token *token)
{
	t_token	*cpy_token;

	cpy_token = token;
	cpy_token = cpy_token->next;
	while (cpy_token && cpy_token->type == WORD)
	{
		if (ft_strcmp(cpy_token->value, "PATH") == 0)
		{
			ft_free_tab(data->paths_system);
			data->paths_system = NULL;
		}
		ft_remove(data->env, cpy_token->value);
		cpy_token = cpy_token->next;
	}
	return ;
}
