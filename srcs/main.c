/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:18:54 by njard             #+#    #+#             */
/*   Updated: 2025/04/21 15:24:39 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define COLOR_PINK "\001\033[38;5;205m\002"
#define COLOR_RED

void	ft_readline(t_data *data)
{
	char *pwd;
	while(1)
	{
		pwd = ft_join(ft_join(COLOR_PINK,ft_search_value(data->env, "PWD")),"\001\033[38;5;198m\002$\001\033[38;5;205m\002 ");
		data->line = readline(pwd);
		free(pwd);
		add_history(data->line);
		data->tokens = lexer(data->line);
		exec(data);
		free(data->line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_data *data;

	data = malloc(sizeof(t_data));
	env = malloc(sizeof(t_env));
	env = env_init(env, envp);
	init_data(data, env);
	// ft_readline(data);

	if (argc >= 2)
	{
		data->tokens = lexer(argv[1]);
		exec(data);
	}
	if (argc >= 3)
	{
		data->tokens = lexer(argv[2]);
		exec(data);
	}
	// if (argc >= 4)
	// 	exec(data, argv[3]);
	// if (argc >= 5)
	// 	exec(data, argv[4]);
	// int i = 0;
	// display_env(env);

    // while (1)
    // {
    //     input = readline(ft_join(search_value(env, "PWD"), "$ "));
    //     if (!input) // Ctrl-D
    //     {
    //         printf("exit\n");
    //         break;
    //     }

    //     if (*input)
    //         add_history(input);
    //     // Ici tu peux parser et exécuter la commande
    //     printf("Tu as tapé : %s\n", input);

    //     free(input); // readline utilise malloc
    // }
	free_data(data);
	// free_env(env);
	return(0);
}
