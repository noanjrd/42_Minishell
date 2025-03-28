/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:54:11 by njard             #+#    #+#             */
/*   Updated: 2025/03/28 14:58:37 by njard            ###   ########.fr       */
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
	int selectioned;
	int displayed;
	struct t_env *next;
}				t_env;

t_env	*env_init(t_env *env, char **envp);
void	free_env(t_env *env);
int	ft_strcmp(char *s1, char *s2);
void	display_export(t_env *env);
void	display_env(t_env *env);
void	ft_unset(t_env *env, char *name);
void ft_export(t_env *env, char *export);
void ft_cd(t_env *env, char *arg);
char	*search_value(t_env *env, char *string);
void change_value(t_env *env, char *name, char *value_to_change);

#endif