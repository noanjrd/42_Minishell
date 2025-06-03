/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:01:56 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 09:21:34 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define COLOR_PINK "\001\033[38;5;205m\002"
#define COLOR_RED

// static void printf_cmd(t_cmd *cmd)
// {
// 	t_cmd *current = cmd;
// 	while (current)
// 	{
// 		printf("value = %s, index=%d infile = %s, outfile = %s, type=%d,here_doc=%d, red_in_avant=%d, red=%d, appnd=%d, end=%d, first=%d, \n",
// 			current->value,
// 			current->index,
// 			current->infile ? current->infile : "NULL",
// 			current->outfile ? current->outfile : "NULL",
// 			current->type,
// 		current->here_doc,
// 		current->redirect_in_before,
// 	current->red_out,
// 	current->red_append,
// current->end,
// 		current->first);
// 		current = current->next;
// 	}
// 	printf("---------------------------\n");
// 	return ;
// }

void	free_readline_data(t_data *data)
{
	if (data->fd_here_doc > 0)
	{
		close(data->fd_here_doc);
		unlink("temp");
	}
	data->fd_here_doc = 0;
	data->error_alrdy_displayed = 0;
	data->nb_of_commands = 0;
	data->tokens = NULL;
	data->line = NULL;
	free_cmd(data->commands);
	data->commands = NULL;
	return ;
}

static void	ft_sigitn(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code_signal = 130;
	}
	return ;
}

t_token	*ft_parse(t_data *data)
{
	data->tokens = lexer(data->line);
	free(data->line);
	data->line = NULL;
	if (ft_check_syntax_errors(data, data->tokens))
	{
		data->exit_code = 2;
		if (data->tokens)
		{
			free_token_list(data->tokens);
			data->tokens = NULL;
		}
		return (NULL);
	}
	data->tokens = ft_dollar_quotes(data->tokens);
	data->tokens = expander(data->tokens, data);
	if (data->tokens)
		merge_tokens(&data->tokens);
	reassign_index(data->tokens);
	return (data->tokens);
}

void	ft_readline(t_data *data)
{
	char	*pwd;
	char	*tmp;

	while (1)
	{
		signal(SIGINT, ft_sigitn);
		signal(SIGQUIT, ft_sigitn);
		tmp = NULL;
		if (data->env)
			tmp = ft_join(COLOR_PINK, ft_search_value(data->env, "PWD"));
		pwd = ft_join(tmp, "\001\033[38;5;198m\002$\001\033[38;5;205m\002 ");
		free(tmp);
		data->line = readline(pwd);
		if (!data->line)
		{
			free(pwd);
			return ;
		}
		if (g_exit_code_signal != 0)
		{
			data->exit_code = g_exit_code_signal;
			g_exit_code_signal = 0;
		}
		free(pwd);
		if (data->line && *data->line)
			add_history(data->line);
		data->tokens = ft_parse(data);
		if (!data->tokens)
			continue ;
		make_commands(data, NULL, NULL, NULL);
		exec_prep(data);
		if (data->tokens)
		{
			free_token_list(data->tokens);
			data->tokens = NULL;
		}
		free_readline_data(data);
	}
}

int	g_exit_code_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_data	*data;
	int		exit_c;

	(void)argv;
	(void)argc;
	exit_c = 0;
	data = malloc(sizeof(t_data));
	env = malloc(sizeof(t_env));
	init_data(data, env, envp);
	ft_readline(data);
	// if (argc >= 2)
	// {
	// 	data->tokens = lexer(argv[1]);
	// 	// print_tokens(data->tokens);
	// 	if (ft_check_syntax_errors(data->tokens) == 0)
	// 	{
	// 		data->tokens = expander(data->tokens, data);
	// 		if (data->tokens)
	// 			merge_tokens(&data->tokens);
	// 		// print_tokens(data->tokens);
	// 		reassign_index(data->tokens);
	// 		make_commands(data, NULL, NULL, NULL);
	// 		// printf_cmd(data->commands);
	// 		exec(data);
	// 		if (data->tokens)
	// 		{
	// 			free_token_list(data->tokens);
	// 			data->tokens = NULL;
	// 		}
	// 		free_cmd(data->commands);
	// 		free_readline_data(data);
	// 	}
	// 	else
	// 	{
	// 		if (data->tokens)
	// 		{
	// 			free_token_list(data->tokens);
	// 			data->tokens = NULL;
	// 		}
	// 	}
	// }
	// if (argc >= 3)srcs/builtins/exit.c\
	// 	// print_tokens(data->tokens);
	// 	if (data->tokens)
	// 		merge_tokens(&data->tokens);
	// 	// print_tokens(data->tokens);
	// 	reassign_index(data->tokens);
	// 	make_commands(data, NULL, NULL, NULL);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// 	if (data->tokens)
	// 	{
	// 		free_token_list(data->tokens);
	// 		data->tokens = NULL;
	// 	}
	// 	free_cmd(data->commands);
	// 	free_readline_data(data);
	// }
	exit_c = data->exit_code;
	free_data(data);
	return (exit_c);
}
