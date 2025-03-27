/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:18:54 by njard             #+#    #+#             */
/*   Updated: 2025/03/27 13:59:32 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*head;

	env = malloc(sizeof(t_env));
	env = env_init(env, envp);
	if (argv[1])
		init_export(argv[1], env);
	int i = 0;
	display_export(env);
	// head = env;
	// while(head)
	// {
	// 	printf("%s=", head->name);
	// 	printf("%s\n", head->value);
	// 	head = head->next;
	// }
	free_env(env);
	return(0);
}
