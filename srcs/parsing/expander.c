/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:36:38 by naankour          #+#    #+#             */
/*   Updated: 2025/05/05 13:36:38 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// je parcours les tokens, chaque fois que j'ai un token word je regarde s'il y a un $,
// si je le trouve je skip le $ et je copie ce qui suit tant que c'est un caractere alphanumérique ou un _
// j'ai le nom de la variable
// avec getenv je cherche dans l'env le nom de cette variable stockée dans value


// maintenant je dois récuperer la totalité du token le copier et afficher la value a la place de la variable
// a la fin remplacer current->value par le contenu du nouveau buffer
// int	ft_isalnum(int c)
// {
// 	if (((c >= 'A' && c <= 'Z')
// 			|| (c >= 'a' && c <= 'z'))
// 		|| (c >= '0' && c <= '9'))
// 		return (1);
// 	return (0);
// }
// int	ft_strlen(char *string)
// {
// 	int i;

// 	i = 0;
// 	while(string[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// fonction qui calcule la taille totale d un token avec une varaible pour malloc

int	get_token_lenght(char *str)
{
	int		len;
	int		i;
	char	name[128];
	char	*value;

	len = 0;
	while (*str)
	{
		i = 0;
		if (*str == '$')
		{
			str++;
			while (ft_isalnum(*str) || *str == '_')
				name[i++] = *str++;
			name[i] = '\0';
			value = getenv(name);
			if (value)
				len = len + ft_strlen(value);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

char	*get_final_token(char *str)
{
	char	*final_buffer;
	int		i;

	final_buffer = malloc(get_token_lenght(str) + 1);
	if (!final_buffer)
		return (NULL);
		while (*str)
		{
			if (*str == '$')
			{
				str++;
				i = 0;
				while (ft_isalnum(*str) || *str == '_')
					final_buffer[i++] = *str++;
		}
		else
			final_buffer[i++] = str++;
		final_buffer[i] = '\0';
	}
	return (final_buffer);
}

void	get_variable_value(t_token *token)
{
	t_token	*current;
	char	*str;
	char	name[128];
	char	*value;
	int		i;

	current = token;
	while (current)
	{
		if ((current->type == WORD) && ft_strchr(current->value, '$'))
		{
			str = current->value;
			i = 0;
			while(*str)
			{
				if (*str == '$')
				{
					str++;
					i = 0;
					while (ft_isalnum(*str) || *str == '_')
						name[i++] = *str++;
					name[i] = '\0';
					value = getenv(name);
					if (!value)
						value = "";
				}
				else
					str++;
			}
		}
		current = current->next;
	}
	return (value);
}

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $1

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $123
// 23
// naankour@c1r3p4:~/Documents/Minishellbis$ echo $dfjkslkgfjsw

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $658
// 58



// t_token	*create_token_variable(char *line, int *index)
// {
// 	int		i;
// 	char	*variable;
// 	int		len;
// 	int		start;

// 	start = *index;
// 	i = start + 1;
// 	len = 0;
// 	i = *index;
// 	variable = malloc(ft_strlen(&line[i]) + 1);
// 	if (!variable)
// 		return (NULL);
// 	i++;
// 	printf("%c", line[i]);
// 	while (ft_isalnum(line[i]) || line[i] == '_')
// 		i++;
// 		variable[len++] = line[i++];
// 	variable[len] = '\0';
// 	*index = i;
// 	return(create_token(VARIABLE, variable));
// }