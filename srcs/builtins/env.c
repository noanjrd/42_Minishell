/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:58:07 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 19:00:36 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	return ;
}
