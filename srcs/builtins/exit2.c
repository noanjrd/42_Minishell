/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:17:32 by naankour          #+#    #+#             */
/*   Updated: 2025/06/02 17:17:32 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	has_too_many_args(t_token *token)
{
	if (!token)
		return (0);
	if (token->next && (token->next->type == WORD
			|| token->next->type == DOUBLE_QUOTES
			|| token->next->type == SINGLE_QUOTES))
		return (1);
	return (0);
}

static void	free_before_exit(t_data *data)
{
	clear_history();
	if (data->tokens)
	{
		free_token_list(data->tokens);
		data->tokens = NULL;
	}
	free_cmd(data->commands);
	if (data->env)
	{
		free_env(data->env);
		data->env = NULL;
	}
	if (data->paths_system)
		ft_free_tab(data->paths_system);
	free(data);
}

void	free_and_exit(t_data *data, int exit_code)
{
	free_before_exit(data);
	exit(exit_code);
}
