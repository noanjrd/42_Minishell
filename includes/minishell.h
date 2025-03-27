/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:54:11 by njard             #+#    #+#             */
/*   Updated: 2025/03/27 13:45:01 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	t_env
{
	char *name;
	char *value;
	struct t_env *next;
}				t_env;

t_env	*env_init(t_env *env, char **envp);
void	free_env(t_env *env);
int	ft_strcmp(char *s1, char *s2);
void init_export(char *export, t_env *env);
void	display_export(t_env *env);

#endif