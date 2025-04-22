/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:54:11 by njard             #+#    #+#             */
/*   Updated: 2025/04/21 12:48:39 by naankour         ###   ########.fr       */
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
	char	*name;
	char	*value;
	int		displayed;
	struct t_env *next;
}				t_env;

typedef enum
{
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	PIPE,
	VARIABLE,
	WORD,
	STRING,
	SIMPLE_QUOTES,
	DOUBLE_QUOTES,
}		t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd
{
	char	**argv;
	char	*infile;
	char	*outfile;
	struct s_cmd *next;
}				t_cmd;

typedef struct t_data
{
	char	**paths_system;
	int		fdin;
	int		fdout;
	int		here_doc;
	char	*line;
	int		exit_code;
	t_env	*env;
	t_token	*tokens;
}				t_data;

// Builtins

void	ft_unset(t_env *env, t_token *token);
void	display_export(t_env *env);
void	display_env(t_env *env);
void ft_export(t_env *env, t_token *token);
void ft_cd(t_env *env, t_token *token);
void	ft_exit(t_data *data, t_token *token);
void	ft_echo(t_data *data, t_env *env, t_token *token);
void	ft_pwd(t_env *env);

// Utils

char	*ft_search_value(t_env *env, char *string);
void	change_value(t_env *env, char *name, char *value_to_change);
int		ft_strstr(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_join(char *s1, char *s2);
char	*ft_copy(char *string);
int		ft_strlen(char *string);
size_t	ft_strlcpy( char *dst, const char *src, size_t size);
int	ft_atoi(const char *nptr);

// Free

void	free_env(t_env *env);
void	free_data(t_data *data);

// Execution

void	exec(t_data *data);
char	*cut_builtin(char *string);
int		check_path_exist(t_data *data, char *instru);
void	here_doc(char *instru, t_data *data);

// Init

t_env	*env_init(t_env *env, char **envp);
void	initalising_path(t_data *data);
void	init_data(t_data *data, t_env *env);

// PARSING

t_token	*create_token(t_token_type type, const char *value);
void	add_token(t_token **head, t_token *new);
void	print_tokens(t_token *head);
t_token	*lexer(char *line);
int	is_space(char c);
int	is_symbol(char c);
t_token	*create_token_word(char *line, int *index);
t_token	*create_token_quotes(char *line, int *index);
int	check_unmatched_quotes(char *line);

#endif