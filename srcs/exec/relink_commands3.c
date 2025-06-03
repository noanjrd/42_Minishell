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

static void advance_past_word_segment(t_token **current_token_ptr,
									   t_token **segment_end_node_ptr)
{
	*segment_end_node_ptr = *current_token_ptr;
	while (*current_token_ptr && ft_check_type(*current_token_ptr) == 0)
	{
		*current_token_ptr = (*current_token_ptr)->next;
		if ((*segment_end_node_ptr)->next &&
			ft_check_type((*segment_end_node_ptr)->next) == 0)
		{
			*segment_end_node_ptr = (*segment_end_node_ptr)->next;
		}
	}
}

static void delete_token_range(t_token *prev_node, t_token *end_node)
{
	t_token *current_to_delete;
	t_token *next_to_delete;

	if (!prev_node)
		return;

	current_to_delete = prev_node->next;
	while (current_to_delete && current_to_delete != end_node)
	{
		next_to_delete = current_to_delete->next;
		ft_free_single_token(current_to_delete);
		current_to_delete = next_to_delete;
	}
	prev_node->next = end_node;
}

static void process_and_merge_segments(t_token **current_processing_token_ptr,
									   t_token *first_segment_start_token,
									   t_token **prev_link_node_ptr,
									   t_cmd *cmd_list)
{
	t_cmd   *cmd1;
	t_cmd   *cmd2;
	t_token *current_target;
	t_token *prev_link_node;

	current_target = *current_processing_token_ptr;
	prev_link_node = *prev_link_node_ptr;
	while (current_target && ft_check_type(current_target) == 0)
	{
		cmd2 = find_cmd_index(current_target, cmd_list);
		if (!cmd2)
		{
			current_target = current_target->next;
			continue;
		}
		cmd1 = find_cmd_index(first_segment_start_token, cmd_list);
		if (!cmd1)
		{
			current_target = current_target->next;
			continue;
		}
		put_tab_recompose(cmd1, cmd2);
		delete_token_range(prev_link_node, current_target);
		prev_link_node = current_target;
		current_target = prev_link_node ? prev_link_node->next : NULL;
	}
	*current_processing_token_ptr = current_target;
	*prev_link_node_ptr = prev_link_node;
}

void ft_check_echo_plus(t_token *token_list, t_cmd *cmd_list, t_token *node_to_delete_unused)
{
	t_token *current_token;
	t_token *first_segment_start;
	t_token *prev_segment_end;

	(void)node_to_delete_unused; 
	current_token = token_list;
	while (current_token)
	{
		if (current_token->type == WORD)
		{
			first_segment_start = current_token;
			advance_past_word_segment(&current_token, &prev_segment_end);
			if (!current_token || !current_token->next ||
				current_token->type == PIPE || !current_token->next->next)
			{
				if (current_token && current_token->next)
					current_token = current_token->next;
				continue;
			}
			current_token = current_token->next->next; // Skip one token (e.g. redirector) and the next one
			process_and_merge_segments(&current_token, first_segment_start,
									   &prev_segment_end, cmd_list);
		}
		else
			current_token = current_token->next;
	}
}


// void ft_check_echo_plus(t_token *token, t_cmd *cmd, t_token *node_to_delete)
// {
// 	t_cmd *temp_cmd;
// 	t_token *cpy_token;
// 	t_token *temp;
// 	t_token *temp2;
// 	t_token *next_to_delete;

// 	temp_cmd = NULL;
// 	cpy_token = token;
// 	while (cpy_token)
// 	{
// 		if (token->type == WORD)
// 		{
// 			temp = cpy_token;
// 			temp2 = cpy_token;
// 			while (cpy_token && ft_check_type(cpy_token) == 0)
// 			{
// 				cpy_token = cpy_token->next;
// 				if (temp2->next && ft_check_type(temp2->next) == 0)
// 					temp2 = temp2->next;
// 			}
// 			if (!cpy_token || !cpy_token->next || cpy_token->type == PIPE || !cpy_token->next->next)
// 			{
// 				if (cpy_token && cpy_token->next)
// 					cpy_token = cpy_token->next;
// 				continue ; 
// 			}
// 			else
// 			{
// 				cpy_token = cpy_token->next->next;
// 			}
// 			while (cpy_token && ft_check_type(cpy_token) == 0)
// 			{
// 				temp_cmd = find_cmd_index(cpy_token, cmd);
// 				if (!temp_cmd)
// 				{
// 					cpy_token = cpy_token->next;
// 					continue;
// 				}
// 				else
// 				{
// 					if (!find_cmd_index(temp, cmd))
// 					{
// 						cpy_token = cpy_token->next;
// 						continue ;
// 					}
// 					put_tab_recompose(find_cmd_index(temp, cmd), find_cmd_index(cpy_token, cmd));
// 					node_to_delete = temp2->next;
// 					while (node_to_delete && node_to_delete != cpy_token)
// 					{
// 						next_to_delete = node_to_delete->next;
// 						ft_free_single_token(node_to_delete);
// 						node_to_delete = next_to_delete;
// 					}
// 					temp2->next = cpy_token; 

// 					temp2 = temp2->next; 
// 					if (temp2)
// 						cpy_token = temp2->next;
// 					else
// 						cpy_token = NULL; 
// 				}
// 			}
// 		}
// 		else
// 			cpy_token = cpy_token->next; 
// 	}
// }

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
