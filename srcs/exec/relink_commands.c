/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   relink_commands.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: njard <njard@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/12 14:22:15 by njard			 #+#	#+#			 */
/*   Updated: 2025/05/29 11:19:29 by njard			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void printf_cmd2(t_cmd *cmd)
// {
// 	t_cmd *current = cmd;
// 	int i = 0;

// 	while (current)
// 	{
// 		i = 0;
// 		printf("val=%s, in=%s, out=%s, fdin=%d, fdout=%d, i=%d, here=%d, appd=%d, path=%s , deleted=%d ",
// 			current->value,
// 			current->infile ? current->infile : "NULL",
// 			current->outfile ? current->outfile : "NULL",
// 			current->fdin,
// 			current->fdout,
// 			current->index,
// 			current->here_doc,
// 			current->red_append,
// 		current->path,
// 	current->deleted);
// 		printf("tab = ");
// 		if (current->tab)
// 		{
// 			while (current->tab && current->tab[i])
// 			{
// 				printf("| %s", current->tab[i]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 		current = current->next;
// 	}
// 	printf("--------------------------------------------\n");
// 	return ;
// }

void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	temp = NULL;
	cmd->red_append = cpy_cmd->red_append;
	cmd->fdout = cpy_cmd->fdout;
	cmd->outfile = ft_copy(cpy_cmd->outfile);
	cmd->tab = ft_join_tab(cmd->tab, cmd->value, cpy_cmd->value);
	cmd->value = ft_join_free(cmd->value, cpy_cmd->value);
	if (cpy_cmd->infile)
		cmd->infile = ft_copy(cpy_cmd->infile);
	temp = cpy_cmd->next;
	free(cpy_cmd->infile);
	free(cpy_cmd->value);
	free(cpy_cmd->tab);
	free(cpy_cmd->fdpipe);
	free(cpy_cmd->outfile);
	free(cpy_cmd);
	cmd->next = temp;
	return ;
}

void	put_tab_recompose(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	temp = NULL;
	cmd->red_append = cpy_cmd->red_append;
	if (cpy_cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = ft_copy(cpy_cmd->outfile);
	}
	cmd->fdout = cpy_cmd->fdout;
	cmd->next->end = 1;
	cmd->tab = ft_join_tab(cmd->tab, cmd->value, cpy_cmd->value);
	cmd->value = ft_join_free(cmd->value, cpy_cmd->value);
	free(cmd->infile);
	cmd->infile = NULL;
	cpy_cmd->deleted = 1;
	return ;
}

t_cmd *find_cmd_index(t_token *token, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	while (cpy_cmd && cpy_cmd->index != token->index)
	{
		cpy_cmd = cpy_cmd->next;
	}
	return (cpy_cmd);
}

void ft_free_single_token(t_token *tok)
{
	if (!tok)
		return;
	free(tok->value);
	free(tok);
}


void ft_check_echo_plus(t_token *token, t_cmd *cmd, t_token *node_to_delete)
{
	t_cmd *temp_cmd;
	t_token *cpy_token;
	t_token *temp;
	t_token *temp2;

	temp_cmd = NULL;
	cpy_token = token;
	while (cpy_token)
	{
		if (token->type == WORD)
		{
			temp = cpy_token;
			temp2 = cpy_token;
			while (cpy_token && ft_check_type(cpy_token) == 0)
			{
				cpy_token = cpy_token->next;
				if (temp2->next && ft_check_type(temp2->next) == 0)
					temp2 = temp2->next;
			}
			if (!cpy_token || !cpy_token->next || cpy_token->type == PIPE || !cpy_token->next->next)
			{
				if (cpy_token && cpy_token->next)
					cpy_token = cpy_token->next;
				continue ; 
			}
			else
			{
				cpy_token = cpy_token->next->next;
			}
			while (cpy_token && ft_check_type(cpy_token) == 0)
			{
				temp_cmd = find_cmd_index(cpy_token, cmd);
				if (!temp_cmd)
				{
					cpy_token = cpy_token->next;
					continue;
				}
				else
				{
					if (!find_cmd_index(temp, cmd))
					{
						cpy_token = cpy_token->next;
						continue ;
					}
					put_tab_recompose(find_cmd_index(temp, cmd), find_cmd_index(cpy_token, cmd));
					node_to_delete = temp2->next;
					while (node_to_delete && node_to_delete != cpy_token)
					{
						t_token *next_to_delete = node_to_delete->next;
						ft_free_single_token(node_to_delete);
						node_to_delete = next_to_delete;
					}
					temp2->next = cpy_token; 

					temp2 = temp2->next; 
					if (temp2)
						cpy_token = temp2->next;
					else
						cpy_token = NULL; 
				}
			}
		}
		else
			cpy_token = cpy_token->next; 
	}
}

void	rest_tab(t_token *token, t_cmd *cpy_cmd)
{
	t_cmd *cmd;

	cmd = cpy_cmd;
	while (cmd)
	{
		if (cmd->tab == NULL)
			cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		cmd = cmd->next;
	}
	ft_check_echo_plus(token, cpy_cmd, NULL);
	return ;
}

void	relink_commands(t_token *cpy_token, t_cmd *cpy_cmd)
{
	t_cmd *cmd;
	t_token *token;

	token = cpy_token;
	cmd = cpy_cmd;
	if (ft_check_type(token) == 1)
	{
		token = token->next->next;
		cmd = cmd->next;
	}
	while (token)
	{
		// if (cmd->next)
		// 	printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->next->value);
		// else
		// 	printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->value);
		if (token->next && cmd && cmd->next && token->type != REDIRECT_OUT && token->type != REDIRECT_APPEND &&token->type != HERE_DOC  &&  token->type != PIPE && token->type != REDIRECT_IN && cmd->next && cmd->type != IN_OUT_FILENAME && ft_check_type(token->next) == 0)
		{
			// printf("join\n");
			put_tab(cmd, cmd->next);
			// token = token->next;
		}
		if (token && token->next && cmd && cmd->next && (ft_check_type(token) == 1))
		{
			while (token->next && cmd->next && token->next->index != cmd->index)
				cmd = cmd->next;
			if (token->next->next && (token->next->type == REDIRECT_OUT || token->next->type == REDIRECT_APPEND))
			{
				cmd = cmd->next;
				token = token->next->next;
				// continue;
			}
			// printf("nddd %s\n", cmd->value);
			// token = token->next;
			// continue;
		}
		// if (cmd->type != IN_OUT_FILENAME || (cmd->next && cmd->next->type == IN_OUT_FILENAME))
		token = token->next;
			
	}
	rest_tab(cpy_token, cpy_cmd);
}


// regarder le cas '< out ls | < infile cat -e'
//cat -e est decolé