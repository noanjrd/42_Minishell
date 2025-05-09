/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:54:11 by njard             #+#    #+#             */
/*   Updated: 2025/05/09 16:49:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int index_t;

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct	t_env
{
	char			*name;
	char			*value;
	int				displayed;
	struct t_env	*next;
}					t_env;

typedef enum
{
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	PIPE,
	VARIABLE,
	WORD,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	IN_OUT_FILENAME
}		t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				index;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char	*value;
	char	**tab;
	char	*infile;
	char	*outfile;
	char *path;
	int	index;
	int fdin;
	int fdout;
	int red_append;
	int here_doc;
	int check_open;
	int path_found;
	struct s_cmd *next;
	t_token_type type;
}				t_cmd;

typedef struct t_data
{
	char	**paths_system;
	int		fd_here_doc;
	int		*fdin;
	int		fdin_index;
	int		fdout;
	int		here_doc;
	char	*line;
	int		exit_code;
	t_env	*env;
	t_token	*tokens;
	t_cmd	*commands;
}				t_data;

// Builtins

t_token	*builtin(t_data *data, t_token *token, char *commands);
void	ft_unset(t_env *env, t_token *token);
void	display_export(t_env *env);
void	display_env(t_env *env);
void	ft_export(t_env *env, t_token *token);
void	ft_cd(t_data *data, t_env *env, t_token *token);
void	ft_exit(t_data *data, t_token *token);
void	ft_echo(t_data *data, t_env *env, t_token *token);
void	ft_pwd(t_env *env);
t_token	*update_echo_struct(t_token *token);

// Utils

char	*ft_search_value(t_env *env, char *string);
void	change_value(t_env *env, char *name, char *value_to_change);
int		ft_strstr(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_join(char *s1, char *s2);
char	*ft_copy(char *string);
int		ft_strlen(char *string);
size_t	ft_strlcpy( char *dst, const char *src, size_t size);
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);


// Free

void	free_env(t_env *env);
void	free_data(t_data *data);

// Execution

void	exec(t_data *data);
void	here_doc(t_token *token, t_data *data);
void	open_fdout(t_data *data, t_token *token, t_cmd *cmd);
void	open_fdin(t_data *data, t_token *token, t_cmd *cmd);
void	relink_commands(t_token *token, t_cmd *cmd);
void	check_path_exist(t_data *data, t_cmd *cmd);

// Init

t_env	*env_init(t_env *env, char **envp);
void	initalising_path(t_data *data);
void	init_data(t_data *data, t_env *env);

// PARSING

t_token	*create_token(t_token_type type, const char *value);
void	add_token(t_token **head, t_token *new);
void	print_tokens(t_token *head);
t_token	*lexer(char *line);
int		is_space(char c);
int		is_symbol(char c);
int		ft_check_syntax_errors(t_token *token);
t_token	*create_token_word(char *line, int *index);
void	expander(t_token *token, t_env	*env);
void	get_variable_value(t_token *token);
void	free_token_list(t_token *head);

#endif