/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:01:56 by njard             #+#    #+#             */
/*   Updated: 2025/05/10 16:19:23 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define COLOR_PINK "\001\033[38;5;205m\002"
#define COLOR_RED

void	rest_ofthesteps(t_token *token, t_cmd *cmd)
{
	t_token *cpy_token;
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC)
		{
			if (cpy_cmd->next)
				cpy_cmd->next->here_doc = 1;
		}
		if (cpy_token->type == PIPE || cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND || cpy_token->type == REDIRECT_IN || cpy_token->type == HERE_DOC)
		{
			cpy_cmd = cpy_cmd->next;
		}
		cpy_token = cpy_token->next;
	}
}

void make_commands(t_data *data)
{
	t_token *cpy_token = data->tokens;
	char *fdin = NULL;
	t_cmd *head = NULL;
	t_cmd *current = NULL;
	int check = 0;
	int out= 0;
	int i = 0;

	while (cpy_token)
	{
		if (cpy_token && (cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN))
		{
			check = 1;
			fdin = cpy_token->next->value;
			// cpy_token = cpy_token->next;
		}
		if (cpy_token && (cpy_token->type == REDIRECT_OUT || cpy_token->type == REDIRECT_APPEND))
		{
			out = 1;
			// printf("wsh\n");
		}
		if (cpy_token->type == WORD || cpy_token->type == SINGLE_QUOTES || cpy_token->type == DOUBLE_QUOTES)
		{
			t_cmd *new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				return;
			new_cmd->fdout = -99;
			new_cmd->fdin = -99;
			new_cmd->check_open = 0;
			new_cmd->here_doc = 0;
			new_cmd->red_append = 0;
			new_cmd->index = i;
			new_cmd->path_found = 0;
			new_cmd->value = ft_copy(cpy_token->value);
			new_cmd->infile = NULL;
			new_cmd->type = WORD;
			// new_cmd->tab = malloc(1);
			new_cmd->tab = NULL;
			if (fdin && check == 3 && !(cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN))
			{
				new_cmd->infile = ft_copy(fdin);
				if (current)
					current->type = IN_OUT_FILENAME;
				fdin = NULL;
				check = 0;
			}
			if (check == 3 && cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN)
				check = 0;
			new_cmd->outfile = NULL;
			new_cmd->next = NULL;
			if (out == 1)
			{
				// printf("lol\n");
				new_cmd->type = IN_OUT_FILENAME;
				out = 0;
			}
			if (!head)
				head = new_cmd;
			else
				current->next = new_cmd;
			current = new_cmd;

		}
		if (cpy_token->next && (cpy_token->next->type == REDIRECT_APPEND || cpy_token->next->type == REDIRECT_OUT))
		{
			if (current)
			{
				current->outfile = ft_copy(cpy_token->next->next->value);
			}
		}
		if (check == 2)
			check =3;
		if (check == 1)
		{
			check = 2;
		}
		i++;
		cpy_token = cpy_token->next;
	}
	data->commands = head;
	rest_ofthesteps(data->tokens, head);
	return ;
}

static void printf_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd;
	while (current)
	{
		printf("value = %s, infile = %s, outfile = %s, type=%d, here_doc=%d\n",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->type,
		current->here_doc);
		current = current->next;
	}
	printf("---------------------------\n");
	return ;
}

void	ft_readline(t_data *data)
{
	char *pwd;
	char *tmp;

	while(1)
	{
		tmp = ft_join(COLOR_PINK,ft_search_value(data->env, "PWD"));
		pwd = ft_join(tmp,"\001\033[38;5;198m\002$\001\033[38;5;205m\002 ");
		free(tmp);
		data->line = readline(pwd);
		free(pwd);
		add_history(data->line);
		data->tokens = lexer(data->line);
		if (ft_check_syntax_errors(data->tokens))
			continue;
		expander(data->tokens, data->env);
		make_commands(data);
		// printf_cmd(data->commands);
		exec(data);
		free(data->line);
		free_token_list(data->tokens);
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
	ft_readline(data);

	// if (argc >= 2)
	// {
	// 	data->tokens = lexer(argv[1]);
	// 	make_commands(data);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// }
	// if (argc >= 3)
	// {
	// 	data->tokens = lexer(argv[2]);
	// 	make_commands(data);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// }
	// if (argc >= 4)
	// {
	// 	data->tokens = lexer(argv[3]);
	// 	make_commands(data);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// }
	// if (argc >= 5)
	// {
	// 	data->tokens = lexer(argv[4]);
	// 	make_commands(data);
	// 	// printf_cmd(data->commands);
	// 	exec(data);
	// }
	free_data(data);
	// free_token_list(data->tokens);
	// free_env(env);
	return(0);
}
