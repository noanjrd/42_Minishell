/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   relink_commands3.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: njard <njard@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/12 14:22:15 by njard			 #+#	#+#			 */
/*   Updated: 2025/06/02 11:21:03 by njard			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_cmd	*find_cmd_index(t_token *token, t_cmd *cmd)
{
	t_cmd	*cpy_cmd;

	cpy_cmd = cmd;
	while (cpy_cmd && cpy_cmd->index != token->index)
	{
		cpy_cmd = cpy_cmd->next;
	}
	return (cpy_cmd);
}

void	ft_free_single_token(t_token *tok)
{
	if (!tok)
		return ;
	free(tok->value);
	free(tok);
}
