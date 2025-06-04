/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:21:11 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 14:00:42 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_type(t_token *token)
{
	if (token->type == PIPE || token->type == REDIRECT_APPEND
		|| token->type == REDIRECT_IN
		|| token->type == REDIRECT_OUT || token->type == HERE_DOC)
	{
		return (1);
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	write(fd, s, i);
}

void	ft_change_value_fd(t_env *env, char *name, char *value)
{
	t_env	*copy;

	if (!env)
	{
		free(value);
	}
	copy = env;
	while (copy)
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
