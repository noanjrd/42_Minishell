/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:54:11 by njard             #+#    #+#             */
/*   Updated: 2025/04/07 14:03:48 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/wait.h>


typedef struct	t_env
{
	char *name;
	char *value;
	int displayed;
	struct t_env *next;
}				t_env;

typedef struct t_data
{
	char	**paths_system;
	int here_doc;
	char *line;
	int	exit_code;
	t_env	*env;
}				t_data;

// Builtins

void	ft_unset(t_env *env, char *name);
void	display_export(t_env *env);
void	display_env(t_env *env);
void ft_export(t_env *env, char *export);
void ft_cd(t_env *env, char *arg);
void	ft_exit(t_data *data);
void	ft_echo(t_env *env, char *arg);

// Utils

char	*ft_search_value(t_env *env, char *string);
void change_value(t_env *env, char *name, char *value_to_change);
int	ft_strstr(char *s1, char *s2);
int	ft_strcmp(char *s1, char *s2);
char *ft_join(char *s1, char *s2);
char	*ft_copy(char *string);
int	ft_strlen(char *string);

// Free

void	free_env(t_env *env);
void free_data(t_data *data);

// Execution

void	exec(t_data *data, char *instru);
char	*cut_builtin(char *string);
int	check_path_exist(t_data *data, char *instru);
void	here_doc(char *instru);

// Init

t_env	*env_init(t_env *env, char **envp);
void	initalising_path(t_data *data);
void	init_data(t_data *data, t_env *env);

#endif