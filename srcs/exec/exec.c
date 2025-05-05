/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:27:36 by njard             #+#    #+#             */
/*   Updated: 2025/05/05 15:06:22 by njard            ###   ########.fr       */
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

void printf_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd;
	while (current)
	{
		printf("value = %s, infile = %s, outfile = %s, fdin = %d, fdout = %d, here_doc = %d, red_append = %d\n",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout,
		current->here_doc,
		current->red_append);
		current = current->next;
	}
	return ;
}

char **ft_join_tab(char **tab, char *value, char *value_app)
{
	int i;
	int j;
	int z;
	char **new_tab;

	i = 0;
	j = 0;
	if (!tab)
	{
		// printf("value = %s, value_app = %s\n", value, value_app);
		new_tab = malloc(3 * sizeof(char *));
		// printf("stttt\n");
		while (value[i])
		{
			i++;
		}
		new_tab[j] = malloc((i + 1) * sizeof(char));
		while (value[i])
		{
			new_tab[j][i] = value[i];
			i++;
		}
		new_tab[j][i] = 0;
		i = 0;
		j++;
		while (value_app[i])
		{
			i++;
		}
		new_tab[j] = malloc((i + 1) * sizeof(char));
		while (value_app[i])
		{
			new_tab[j][i] = value_app[i];
			i++;
		}
		new_tab[j][i] = 0;
		new_tab[2] = NULL;
		return (new_tab);
	}
	// faire la suite quand il y a plusieurs tirés 'ls -la -l'
	return (new_tab);
}

char *ft_join_free(char *s1, char *s2)
{
	int i;
	int j;
	char *new_string;

	i = 0;
	j = 0;
	while(s1[i])
		i++;
	while(s2[j])
		j++;
	new_string = malloc((i + j + 2) * sizeof(char));
	if (!new_string)
		return(NULL);
	i = 0;
	j = 0;
	while(s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = ' ';
	i++;
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = 0;
	free(s1);
	// free(s2);
	return(new_string);
}

void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	// cmd->red_append = cpy_cmd->red_append;
	cmd->tab = ft_join_tab(cmd->tab, cmd->value, cpy_cmd->value);
	cmd->value = ft_join_free(cmd->value, cpy_cmd->value);
	temp = cpy_cmd->next;
	free(cpy_cmd->infile);
	free(cpy_cmd->value);
	free(cpy_cmd->tab);
	free(cpy_cmd->outfile);
	free(cpy_cmd);
	cmd->next = temp;
	return ;
}

void	relink_commands(t_token *token, t_cmd *cmd)
{
	// t_cmd *cpy_cmd;
	int i; 

	i = 0;
	// cpy_cmd = cmd->next;
	while (token)
	{
		if (cmd->next)
			printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->next->value);
		else
			printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->value);
		if (token->next &&  cmd->type != IN_OUT_FILENAME)
		{
			printf("lol\n");
			put_tab(cmd, cmd->next);
			token = token->next;
			if (cmd->next && token->next && (token->next->type == REDIRECT_OUT || token->next->type == PIPE) )
				cmd = cmd->next;
		}
		printf("next\n");
		if (token && cmd->next && ft_strcmp(token->value, cmd->value) == 0)
		{
			cmd = cmd->next;
			printf("nddd %s\n", cmd->value);
			// token = token->next;
		}
		i++;
		token = token->next;
	}
	return ;
}

void	exec(t_data *data)
{
	int i;

	i = 0;
	t_token *cpy_token;
	t_cmd *cpy_cmd;

	cpy_cmd = data->commands;
	cpy_token = data->tokens;
	// printf_cmd(cpy_cmd);
	relink_commands(cpy_token, cpy_cmd);
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
		if (ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
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
			open_fdin(data, cpy_token, cpy_cmd);
		}
		if (cpy_cmd->infile && cpy_cmd->fdin == -99)
		{
			if (cpy_cmd->here_doc == 0)
				cpy_cmd->fdin = open(cpy_cmd->infile, O_WRONLY | O_CREAT , 0644);
			if (cpy_cmd->here_doc == 0)
				cpy_cmd->fdin = data->fd_here_doc;
			}
		if (ft_strcmp(cpy_token->value, cpy_cmd->value) == 0)
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
