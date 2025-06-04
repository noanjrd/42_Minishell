/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:34:00 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 16:00:06 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_root(void)
{
	char	*path;

	path = malloc(2 * sizeof(char));
	if (!path)
		return (NULL);
	path[0] = '/';
	path[1] = 0;
	return (path);
}
