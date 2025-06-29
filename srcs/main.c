/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:01:56 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 15:10:33 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define COLOR_PINK "\033[38;5;218m"

static t_token	*ft_parse(t_data *data)
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

static void	ft_readline2(t_data *data)
{
	if (data->line && *data->line)
		add_history(data->line);
	data->tokens = ft_parse(data);
	if (!data->tokens)
		return ;
	make_commands(data, NULL, NULL, NULL);
	exec_prep(data);
	if (data->tokens)
	{
		free_token_list(data->tokens);
		data->tokens = NULL;
	}
	free_readline_data(data);
}

void	ft_readline(t_data *data)
{
	char	*pwd;
	char	*tmp;

	while (1)
	{
		ft_sig_main();
		tmp = NULL;
		if (data->env)
			tmp = ft_join(COLOR_PINK, ft_search_value(data->env, "PWD"));
		pwd = ft_join(tmp, "\001\033[38;5;198m\002$\001\033[38;5;205m\002 ");
		free(tmp);
		data->line = readline(pwd);
		free(pwd);
		if (!data->line)
		{
			printf("exit\n");
			return ;
		}
		if (g_exit_code_signal != 0)
		{
			data->exit_code = g_exit_code_signal;
			g_exit_code_signal = 0;
		}
		ft_readline2(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_data	*data;
	int		exit_c;

	(void)argv;
	(void)argc;
	exit_c = 0;
	data = malloc(sizeof(t_data));
	if (envp && envp[0] != NULL)
		env = malloc(sizeof(t_env));
	else
		env = NULL;
	init_data(data, env, envp);
	ft_readline(data);
	exit_c = data->exit_code;
	free_data(data);
	return (exit_c);
}
