/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:01:56 by njard             #+#    #+#             */
/*   Updated: 2025/05/28 12:29:47 by njard            ###   ########.fr       */
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
// 		printf("value = %s, infile = %s, outfile = %s, type=%d,here_doc=%d, red_in_avant=%d, red=%d, appnd=%d, end=%d, first=%d, \n",
// 			current->value,
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
	data->commands = NULL;
	return ;
}

static void	ft_sigitn(int sig)
{
	if (sig == SIGINT)
	{
		write(1,"\n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

// void	ft_signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = ft_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;

// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
// }

void	ft_readline(t_data *data)
{
	char *pwd;
	char *tmp;

	while(1)
	{
		signal(SIGINT ,ft_sigitn);
		signal(SIGQUIT ,ft_sigitn);
		tmp = NULL;
		if (data->env)
			tmp = ft_join(COLOR_PINK,ft_search_value(data->env, "PWD"));
		pwd = ft_join(tmp,"\001\033[38;5;198m\002$\001\033[38;5;205m\002 ");
		free(tmp);
		data->line = readline(pwd);
		if (!data->line)
		{
			free(pwd);
			// free_data(data);
			return ;
		}
		free(pwd);
		add_history(data->line);
		data->tokens = lexer(data->line);
		free(data->line);
		if (ft_check_syntax_errors(data->tokens))
			continue;
		data->tokens = expander(data->tokens, data);
		if (data->tokens)
			merge_tokens(&data->tokens);
		reassign_index(data->tokens);
		// print_tokens(data->tokens);
		make_commands(data, NULL, NULL, NULL);
		exec(data);
		if (data->tokens)
		{
			free_token_list(data->tokens);
			data->tokens = NULL;
		}
		free_cmd(data->commands);
		free_readline_data(data);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	t_data *data;

	data = malloc(sizeof(t_data));
	env = malloc(sizeof(t_env));
	init_data(data, env, envp);
	// ft_signals();
	ft_readline(data);

	if (argc >= 2)
	{
		data->tokens = lexer(argv[1]);
		data->tokens = expander(data->tokens, data);
		// print_tokens(data->tokens);
		if (data->tokens)
			merge_tokens(&data->tokens);
		// print_tokens(data->tokens);
		reassign_index(data->tokens);
		make_commands(data, NULL, NULL, NULL);
		// printf_cmd(data->commands);
		exec(data);
		if (data->tokens)
		{
			free_token_list(data->tokens);
			data->tokens = NULL;
		}
		free_cmd(data->commands);
		free_readline_data(data);
	}
	if (argc >= 3)
	{
		data->tokens = lexer(argv[2]);
		// print_tokens(data->tokens);
		data->tokens = expander(data->tokens, data);
		// print_tokens(data->tokens);
		if (data->tokens)
			merge_tokens(&data->tokens);
		// print_tokens(data->tokens);
		reassign_index(data->tokens);
		make_commands(data, NULL, NULL, NULL);
		// printf_cmd(data->commands);
		exec(data);
		if (data->tokens)
		{
			free_token_list(data->tokens);
			data->tokens = NULL;
		}
		free_cmd(data->commands);
		free_readline_data(data);
	}
	// if (argc >= 4)
	// {
	// 	data->tokens = lexer(argv[3]);
	// 	make_commands(data,NULL, NULL, NULL);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// 	free_readline_data(data);
	// }
	// if (argc >= 5)
	// {
	// 	data->tokens = lexer(argv[4]);
	// 	make_commands(data,NULL, NULL, NULL);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// }
	free_data(data);
	// free_token_list(data->tokens);
	// free_env(env);
	return(0);
}

// exit sans rien apres exit avec code 127