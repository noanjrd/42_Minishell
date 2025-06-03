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


static void ft_condition_one(t_token **token, t_cmd **cmd)
{
	t_token *t;
	t_cmd *c;

	t = *token;
	c = *cmd;
	while (t->next && ft_check_type(t) != 0)
	{
		t = t->next;
		if (t->type == REDIRECT_OUT || t->type == REDIRECT_APPEND 
			|| t->type == REDIRECT_IN || t->type == HERE_DOC)
			c = c->next;		
	}
	if (t->index != c->index)
		c = c->next;
	*token = t;
	*cmd = c;
}

static int ft_condition_two(t_token *token, t_cmd *cmd)
{
	if (token->next && cmd && cmd->next 
			&& ft_check_type(token) == 0
			&& cmd->next && cmd->type != IN_OUT_FILENAME 
			&& ft_check_type(token->next) == 0)
		return (1);
	return (0);
}

static void	ft_condition_three(t_token **token, t_cmd **cmd)
{
	t_token *t;
	t_cmd *c;

	t = *token;
	c = *cmd;

	c = c->next;
	while (t->next && t->index != c->index)
		t = t->next;
	*token = t;
	*cmd = c;
	return ;
}

static void	ft_condition_four(t_token **token, t_cmd **cmd)
{
	t_token *t;
	t_cmd *c;

	t = *token;
	c = *cmd;
	t = t->next->next;
	c = c->next;
	*token = t;
	*cmd = c;
	return ;
}

void	relink_commands(t_token *cpy_token, t_cmd *cpy_cmd)
{
	t_cmd *cmd;
	t_token *token;

	token = cpy_token;
	cmd = cpy_cmd;
	if (ft_check_type(token) == 1)
		ft_condition_four(&token, &cmd);
	while (token)
	{
		if (ft_condition_two(token, cmd) == 1)
			put_tab(cmd, cmd->next);
		if (token && token->next && cmd && cmd->next 
			&& (ft_check_type(token) == 1))
		{
			ft_condition_one(&token, &cmd);
			continue;
		}
		if (cmd->next && ft_strcmp(token->value, cmd->value) == 0)
		{
			ft_condition_three(&token, &cmd);
			continue;
		}
		token = token->next;
	}
	rest_tab(cpy_token, cpy_cmd);
}


// < infile ls | < infile cat -e
//cat -e est decolé
// echo hi >>out >outfile01 | echo bye
// ls <123 <456 hi | echo 42
// echo hi | >outfile echo bye >infile