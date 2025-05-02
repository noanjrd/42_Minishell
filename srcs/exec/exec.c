/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/05/02 11:43:44 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*builtin_second(t_data *data, t_token *token, char *commands)
{
	char *arg;

	arg = NULL;
	if (ft_strcmp(commands, "export") == 0)
	{
		ft_export(data->env, token);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "cd") == 0)
	{
		ft_cd(data, data->env, token->next);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "pwd") == 0)
	{
		ft_pwd(data->env);
		return (free(arg), token->next);
	}
	return (token->next);
}

t_token	*builtin(t_data *data, t_token *token, char *commands)
{
	char *arg;
	
	arg = NULL;

	if (ft_strcmp(commands, "echo") == 0)
	{
		ft_echo(data, data->env, token);
		return (free(arg), update_echo_struct(token));
	}
	if (ft_strcmp(commands, "unset") == 0)
	{
		ft_unset(data->env, token);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "env") == 0)
	{
		display_env(data->env);
		return (free(arg), token->next);
	}
	if (ft_strcmp(commands, "exit") == 0)
	{
		ft_exit(data, token);
	}
	return(builtin_second(data, token, commands));
}

// void	open_fd(t_data *data, t_token *token)
// {
// 	data->fdin[data->fdin_index] = open(token->value, O_WRONLY | O_CREAT , 0644);
// 	if (data->fdin[data->fdin_index] < 0)
// 	{
// 		printf("error");
// 	}
// 	return ;
// }

// void	ft_modify_command_fdout(t_data *data,char *value,  int fdout, char *outfile)
// {
// 	t_cmd	*cpy;

// 	cpy = data->commands;

// 	while(data->commands)
// 	{
// 		if (comm)
// 	}
// }

void printf_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd;
	while (current)
	{
		printf("value = %s, infile = %s, outfile = %s, fdin = %d, fdout = %d\n",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout);
		current = current->next;
	}
	return ;
}

void	relink_fdin_token(t_token *token, t_token *cpy_token)
{
	t_token	*temp;
	t_token	*start;

	start = token;
	free(token->value);
	token->value = ft_copy(cpy_token->value);
	token = token->next;
	while (token && token->index != cpy_token->index)
	{
		temp = token->next;
		free(token->value);
		free(token);
		token = temp;
	}
	token = start;
	return ;
}

void	open_fdin(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd	*cpy_cmd;
	int fdin;
	cpy_token = token;
	cpy_cmd = cmd;
	int check = 0;

	printf("|%s|\n", cpy_token->value);
	while (cpy_token->next->next && cpy_cmd->next->next && (cpy_cmd->next->next->type == IN_OUT_FILENAME || cpy_token->next->next->type == HERE_DOC || cpy_token->next->next->type == REDIRECT_IN))
	{
		check = 1;
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next->next;
	}
	printf("%s\n", cpy_token->value);
	if (check == 1)
		relink_fdin_token(token, cpy_token);
	return ;
}

void	exec(t_data *data)
{
	int i;

	i = 0;
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
		{
			here_doc(cpy_token, data);
		}
		cpy_token = cpy_token->next;
	}
	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token)
	{
		if (cpy_token->next && (cpy_token->next->type == REDIRECT_OUT || cpy_token->next->type == REDIRECT_APPEND))
		{
			open_fdout(data, cpy_token, cpy_cmd);
		}
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	cpy_token = data->tokens;
	cpy_cmd = data->commands;
	while (cpy_token)
	{
		if (cpy_token->next && (cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC) )
		{
			printf("lol\n");
			open_fdin(data, cpy_token, cpy_cmd);
		}
	// 	if (cpy_token->next && cpy_token->next->next && (cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC))
	// 	{
	// 		cpy_token = cpy_token->next->next;
	// 		if (cpy_cmd && cpy_cmd->next)
	// 			cpy_cmd = cpy_cmd->next;
	// 	}
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	printf_cmd(cpy_cmd);
	print_tokens(cpy_token);
	while (cpy_token)
	{
		if (cpy_token->type == WORD)
		{
			cpy_token = builtin(data, cpy_token, cpy_token->value);
		}
		else
			cpy_token = cpy_token->next;
	}
	// if (builtin(data, data->env, instru) == 1)
	// {
	// 	// printf("builtin\n");
	// 	return ;
	// }
	// // initalising_path(data);
	// if (check_path_exist(data, instru) == 1)
	// {
	// 	// printf("other\n");
	// 	// printf("wsh\n");
	// 	return;
	// }
	// if (ft_strstr(instru, "<<"))
	// {
	// 	// printf("here\n");
	// 	here_doc(instru);
	// 	// printf("wsh\n");
	// 	return;
	// }
	// printf("%s\n",instru);
	// printf("%d\n",ft_strstr(instru, "export"));
	return ;
}
