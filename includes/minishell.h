/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:54:11 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 13:03:42 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/sysmacros.h>

# define NEW_LINE "minishell: syntax error near unexpected token `newline'\n"
# define TOKEN "minishell: syntax error near unexpected token `%s'\n"
# define DOUBLE_PIPE "minishell: syntax error near unexpected token `||'\n"
# define SINGLE_PIPE "minishell: syntax error near unexpected token `|'\n"
# define S_HERE_DOC "minishell: syntax error near unexpected token `<<'\n"
# define APPEND "minishell: syntax error near unexpected token `>>'\n"

extern int	g_exit_code_signal;

typedef struct t_env
{
	char			*name;
	char			*value;
	int				displayed;
	struct t_env	*next;
}					t_env;

typedef enum t_enum
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
	int				has_space;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			*value;
	char			**tab;
	char			*infile;
	char			*outfile;
	char			*path;
	int				*fdpipe;
	int				*prev_fdpipe;
	int				index;
	int				fdin;
	int				fdout;
	pid_t			pid;
	int				red_append;
	int				red_out;
	int				here_doc;
	int				end;
	int				first;
	int				check_fdout;
	int				check_fdin;
	int				redirect_in_before;
	int				deleted;
	struct s_cmd	*next;
	t_token_type	type;
}					t_cmd;

typedef struct s_str
{
	char	*str;
	int		i;
}				t_str;

typedef struct t_data
{
	char	**paths_system;
	int		fd_here_doc;
	char	*line;
	char	**envp;
	int		exit_code;
	int		nb_of_commands;
	int		error_alrdy_displayed;
	t_env	*env;
	t_token	*tokens;
	t_cmd	*commands;
}						t_data;

// BUILTINS
void	ft_unset(t_env *env, t_token *token);
void	display_env(t_env *env);
void	ft_cd(t_data *data, t_env *env, t_token *token);
void	free_and_exit(t_data *data, int exit_code);
void	ft_echo(t_data *data, t_token *token);
void	ft_pwd(void);
t_token	*update_echo_struct(t_token *token);
int	builtin_check(t_cmd *cmd);
void	go_to_right_builtin(t_data *data, int i);
char	*cd_root(void);
void	cd_error(t_data *data);
void	go_into_specific_dr(t_data *data, t_env *env,
			char *current, char *path);
void	absolute_path(t_env *env, char *path);

// EXPORT
void	ft_export(t_data *data, t_env *env, t_token *token);
void	export_merge(t_env *env, char *name, char *value);
int		check_plus(char *export);
void	create_export(t_env *env, char *name, char *value);
int		check_alrdy_exist(t_env *env, char *name, char *value, char *export);
void	display_export(t_env *env);
int		check_valid_name(char *name, int check);
int	ft_check_first_character(t_token *token_copy);

// UTILS
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
char	*ft_itoa(int n);
void	ft_free_tab(char **tab);
int		ft_check_type(t_token *token);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoll(char *str, long long *result);
char	*ft_strdup(char *src);

// FREE
void	free_env(t_env *env);
void	free_data(t_data *data);
void	free_cmd(t_cmd *cmd);
void	free_token_list(t_token *head);
void	free_readline_data(t_data *data);
void	ft_exit(t_data *data, t_token *token);

// EXECUTION
void	exec_prep(t_data *data);
void	here_doc(t_token *token, t_data *data);
void	open_fdout(t_token *token, t_cmd *cmd);
void	relink_commands(t_token *token, t_cmd *cmd);
void	check_path_exist(t_data *data, t_cmd *cmd);
void	exec(t_data *data);
void	fdin_after(t_data *data, t_cmd *cmd);
void	fdin_before(t_data *data, t_cmd *cmd);
char	**ft_join_tab(char **tab, char *value, char *value_app);
char	*ft_join_free(char *s1, char *s2);
void	fd_error(t_data *data, int fd);
void	excve_apply(t_data *data, t_cmd *cmd, t_cmd *cmd_temp);
void	printf_error_beginning(t_data *data, t_cmd *cmd, int error);
void	ft_error_fork(t_data *data);
void	dup_cases(t_cmd *cmd);
void	wait_p(t_data *data);
void	rest_tab(t_token *token, t_cmd *cpy_cmd);
void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd);
void	put_tab_recompose(t_cmd *cmd, t_cmd *cpy_cmd);
t_cmd *find_cmd_index(t_token *token, t_cmd *cmd);
void ft_free_single_token(t_token *tok);
void	ft_skip_words(t_token **t, t_token **temp_arg);
void ft_check_echo_plus(t_token *token, t_cmd *cmd);
void ft_process_word_type_token(t_token **current_node, t_cmd *cmd);

// INIT
t_env	*env_init(t_env *env, char **envp);
void	initalising_path(t_data *data);
void	init_data(t_data *data, t_env *env, char **envp);
void	make_commands(t_data *data, t_cmd *head, t_cmd *current,
			t_cmd *new_cmd);
void	rest_ofthesteps_one(t_token *token, t_cmd *cmd);
void	rest_ofthesteps_two(t_token *token, t_cmd *cmd);
void	rest_ofthesteps_four(t_cmd *cmd, int check);

// PARSING
t_token	*lexer(char *line);
void	skip_whitespaces(char *line, int *i);
int		is_symbol(char c);
t_token	*create_token_word(char *line, int *index);
int		is_space(char c);
t_token	*create_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *new);
int		ft_check_syntax_errors(t_data *data, t_token *token);
void	skip_spaces2(char *line, int *i);
t_token	*ft_dollar_quotes(t_token *tokens);

// EXPANDER
t_token	*expander(t_token *token, t_data *data);
char	*new_token_value(char *str, t_data	*data);
int		ft_handle_dollar(t_str *src, char *final_buffer, int j, t_data *data);
void	merge_tokens(t_token	**token);
void	reassign_index(t_token *tokens);

#endif