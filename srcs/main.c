/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:18:54 by njard             #+#    #+#             */
/*   Updated: 2025/04/03 14:56:35 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data, t_env *env)
{
	data->paths_system = NULL; 
	data->env = env;
	initalising_path(data);
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*head;
	t_data *data;

	data = malloc(sizeof(t_data));
	env = malloc(sizeof(t_env));
	env = env_init(env, envp);
	init_data(data, env);
	if (argc >= 2)
		exec(data, argv[1]);
	if (argc >= 3)
		exec(data, argv[2]);
	if (argc >= 4)
		exec(data, argv[3]);
	// if (argv[4][0])
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
