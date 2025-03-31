/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:18:54 by njard             #+#    #+#             */
/*   Updated: 2025/03/31 11:30:21 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*head;
	char *input;

	env = malloc(sizeof(t_env));
	env = env_init(env, envp);
	if (argv[1])
		ft_echo(env, argv[1]);
	int i = 0;
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

	free_env(env);
	return(0);
}
