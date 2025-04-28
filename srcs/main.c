/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: njard <njard@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/26 11:18:54 by njard			 #+#	#+#			 */
/*   Updated: 2025/04/28 11:45:21 by njard			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

#define COLOR_PINK "\001\033[38;5;205m\002"
#define COLOR_RED

void make_commands(t_data *data)
{
	t_token *cpy_token = data->tokens;
	char *fdin = NULL;
	t_cmd *head = NULL;
	t_cmd *current = NULL;
	int check = 0;

	while (cpy_token)
	{
		if (cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN)
		{
			check = 1;
			fdin = cpy_token->next->value;
			// cpy_token = cpy_token->next;
		}

		if (cpy_token->type == WORD)
		{
			t_cmd *new_cmd = malloc(sizeof(t_cmd));
			new_cmd->fdout = 0;
			new_cmd->fdin = 0;
			if (!new_cmd)
				return;

			new_cmd->value = cpy_token->value;
			if (fdin && check == 3 && !(cpy_token->type == HERE_DOC || cpy_token->type == REDIRECT_IN))
			{
				new_cmd->infile = ft_copy(fdin);
				fdin = NULL; 
				check = 0;
			}
			new_cmd->outfile = NULL;
			new_cmd->next = NULL;

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
				current->outfile = cpy_token->next->next->value;
			}
		}
		if (check == 2)
			check =3;
		if (check == 1)
			check = 2;

		cpy_token = cpy_token->next;
	}

	data->commands = head;
}

static void printf_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd;
	while (current)
	{
		printf("value = %s, fdin = %s, fdout = %s\n",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL");
		current = current->next;
	}
	return ;
}

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
		make_commands(data);
		printf_cmd(data->commands);
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
	ft_readline(data);

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
	if (argc >= 4)
	{
		data->tokens = lexer(argv[3]);
		exec(data);
	}
	if (argc >= 5)
	{
		data->tokens = lexer(argv[4]);
		exec(data);
	}
	free_data(data);
	// free_env(env);
	return(0);
}
