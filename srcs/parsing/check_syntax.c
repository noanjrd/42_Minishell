/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:27 by naankour          #+#    #+#             */
/*   Updated: 2025/04/17 12:29:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_syntax_errors(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if ((current->type == REDIRECT_IN || current->type == REDIRECT_OUT || current->type == HERE_DOC || current->type == REDIRECT_APPEND)
			&& (current->next == NULL || (current->next->type != WORD && current->next->type != DOUBLE_QUOTES && current->next->type != SINGLE_QUOTES)))
		{
			printf("syntax error near unexpected token ´%s'\n", current->value);
			return (1);
		}
		if ((current->next && current->type == PIPE) && current->next->type == PIPE)
		{
			printf("syntax error near unexpected token ´||'\n");
			return (1);
		}
		if ((current == token && current->type == PIPE) || (current->type == PIPE && current->next == NULL))
		{
			printf("syntax error near unexpected token ´||'\n");
			return (1);
		}
		current = current->next;
	}
	return (0);
}
// Test  61: ❌ echo <"./test_files/infile" "bonjour       42"
// mini output = (syntax error near unexpected token ´<')
// bash output = (bonjour 42)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  62: ❌ cat <"./test_files/file name with spaces"
// mini output = (syntax error near unexpected token ´<')
// bash output = (😈 😈 😈 This will break your minishell 😈 😈 😈)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  64: ❌ cat <"1""2""3""4""5"
// mini output = (syntax error near unexpected token ´<')
// bash output = ()
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 1
// mini error = ()
// bash error = ( No such file or directory)
// Test  65: ❌ echo <"./test_files/infile" <missing <"./test_files/infile"
// mini output = (syntax error near unexpected token ´<')
// bash output = ()
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 1
// mini error = ()
// bash error = ( No such file or directory)
// Test  66: ❌ echo <missing <"./test_files/infile" <missing
// mini output = (syntax error near unexpected token ´<')
// bash output = ()
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 1
// mini error = ()
// bash error = ( No such file or directory)
// Test  67: ❌ cat <"./test_files/infile"
// mini output = (syntax error near unexpected token ´<')
// bash output = (hi hello world 42)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  68: ❌ echo <"./test_files/infile_big" | cat <"./test_files/infile"
// mini output = (syntax error near unexpected token ´<')
// bash output = (hi hello world 42)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  69: ❌ echo <"./test_files/infile_big" | cat "./test_files/infile"
// mini output = (syntax error near unexpected token ´<')
// bash output = (hi hello world 42)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  70: ❌ echo <"./test_files/infile_big" | echo <"./test_files/infile"
// mini output = (syntax error near unexpected token ´<')
// bash output = ()
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  71: ❌ echo hi | cat <"./test_files/infile"
// mini output = (syntax error near unexpected token ´<')
// bash output = (hi hello world 42)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  72: ✅ echo hi | cat "./test_files/infile"
// Test  73: ❌ cat <"./test_files/infile" | echo hi
// mini output = (syntax error near unexpected token ´<')
// bash output = (hi)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// mini error = ()
// bash error = ( Broken pipe)
// Test  74: ❌ cat <"./test_files/infile" | grep hello
// mini output = (syntax error near unexpected token ´<')
// bash output = (hello)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// Test  75: ❌ cat <"./test_files/infile_big" | echo hi
// mini output = (syntax error near unexpected token ´<')
// bash output = (hi)
// mini exit code = syntax error near unexpected token ´<'
// bash exit code = 0
// mini error = ()
// bash error = ( Broken pipe)
// Test  86: ❌ ls >"./outfiles/outfile with spaces"
// Only in ./bash_outfiles: outfile with spaces
// mini outfiles:
// cat: './mini_outfiles/*': No such file or directory
// bash outfiles:
// bash_outfiles
// bash.supp
// bonus
// bonus_bonus
// builtins
// extras
// local.supp
// loop.out
// manual_tests
// mini_outfiles
// os_specific
// outfiles
// pipes
// README.md
// redirects
// syntax
// tester
// test_files
// wildcards
// mini output = (syntax error near unexpected token ´>')
// bash output = ()
// mini exit code = syntax error near unexpected token ´>'
// bash exit code = 0
// Test  87: ❌ ls >"./outfiles/outfile""1""2""3""4""5"
// Only in ./bash_outfiles: outfile12345
// mini outfiles:
// cat: './mini_outfiles/*': No such file or directory
// bash outfiles:
// bash_outfiles
// bash.supp
// bonus
// bonus_bonus
// builtins
// extras
// local.supp
// loop.out
// manual_tests
// mini_outfiles
// os_specific
// outfiles
// pipes
// README.md
// redirects
// syntax
// tester
// test_files
// wildcards
// mini output = (syntax error near unexpected token ´>')
// bash output = ()
// mini exit code = syntax error near unexpected token ´>'
// bash exit code = 0
