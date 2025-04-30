/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:25:03 by njard             #+#    #+#             */
/*   Updated: 2025/04/30 13:16:38 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *cut_builtin_echo(char *string)
{
	int i;
	int j;
	char *arg;

	i = 0;
	j = 0;
	while(string[i] == ' ' || (string[i] >= 7 && string[i] <= 13 ))
		i++;
	while(string[i] && string[i] != ' ' && !(string[i] >= 7 && string[i] <= 13 ))
		i++;
	i++;
	while(string[i + j])
		j++;
	arg = malloc((j + 1) * sizeof(char));
	if (!arg)
		return (NULL);
	j = 0;
	while(string[j + i] )
	{
		arg[j] = string[i + j];
		j++;
	}
	arg[j] = 0;
	return (arg);
}

static int	value_env(t_data *data, t_env *env, char *arg, int i)
{
	int j;
	char *name;
	char *value;

	j = 0;
	// printf("%s\n", arg);
	if (arg[0] == '$' && arg[1] == '?')
	{
		printf("%d", data->exit_code);
		return (1);
	}
	while (arg[i + j] && arg[i + j] != ' ')
		j++;
	name = malloc((j + 1) * sizeof(char));
	if (!name)
		return (i);
	j = 0;
	while (arg[i] && arg[i] != ' ')
	{
		name[j] = arg[i];
		i++;
		j++;
	}
	name[j] =  '\0';
	// printf("%s\n", name);
	value = ft_search_value(env, name);
	printf("%s", value);
	// free(value);
	free(name);
	// printf("%d\n", i);
	return (j);
}

t_token *update_echo_struct(t_token *token)
{
	while (token && (token->type == WORD || token->type == SINGLE_QUOTES || token->type == DOUBLE_QUOTES))
		token = token->next;
	return token;
}

void	ft_echo(t_data *data, t_env *env, t_token *token)
{
	int i;
	int n;
	char *arg;

	n = 0;
	t_token *copy_token = token;
	if (!copy_token->next)
	{
		printf("\n");
		data->exit_code = 0;
		return ;
	}
	// printf("coucou\n");
	copy_token = copy_token->next;
	// printf("%s\n",copy_token->value );
	if (copy_token && copy_token->type ==  WORD || copy_token->type ==  SINGLE_QUOTES || copy_token->type ==  DOUBLE_QUOTES || copy_token->type == VARIABLE)
	{
		if (copy_token->value[0] == '$' && copy_token->value[1] == '?')
		{
			printf("%d\n", data->exit_code);
			return ;
		}
	}
	while (copy_token && (copy_token->type ==  WORD || copy_token->type ==  SINGLE_QUOTES || copy_token->type ==  DOUBLE_QUOTES))
	{
		if (copy_token->value[0] == '-' && copy_token->value[1] == 'n')
			n = 1;
		else
			break;
		copy_token = copy_token->next;
	}
	while (copy_token && (copy_token->type ==  WORD || copy_token->type == SINGLE_QUOTES || copy_token->type == DOUBLE_QUOTES))
	{
		printf("%s", copy_token->value);
		if (copy_token->next && (copy_token->next->type ==  WORD || copy_token->type == SINGLE_QUOTES || copy_token->type == DOUBLE_QUOTES))
			printf(" ");
		copy_token = copy_token->next;
	}
	if (n == 0)
		printf("\n");
	data->exit_code = 0;
	return ;
}

// void	ft_echo(t_data *data, t_env *env, char *commands)
// {
// 	char *arg;

// 	arg = cut_builtin_echo(commands);
// 	// printf("%s\n",arg);
// 	if (arg[0] == '$' && arg[1] == '?')
// 		printf("%d\n", data->exit_code);
// 	ft_echo_next(env, commands);
// 	free(arg);
// 	return ;
// }
