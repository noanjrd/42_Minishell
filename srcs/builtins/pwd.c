/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:08:50 by njard             #+#    #+#             */
/*   Updated: 2025/04/08 14:17:01 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_env *env)
{
	char *get_pwd;

	get_pwd = getcwd(NULL, 0);
	printf("%s\n", get_pwd);
	free(get_pwd);
	return ;
}
