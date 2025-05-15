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

int	get_token_lenght(char *str, t_env *env)
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
			value = ft_copy(ft_search_value(env, name));
			if (value)
				len = len + ft_strlen(value);
		}
		else
		{
			len++;
			str++;
		}
	}
	free (value);
	return (len);
}

char	*new_token_value(char *str, t_data	*data)
{
	int		i;
	char	name[128];
	int		name_len;
	char	*value;
	char	*final_buffer;
	int		j;
	int		k;
	char	*str_exit_code;

	final_buffer = malloc(get_token_lenght(str, data->env) + 1);
	if (!final_buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str_exit_code = ft_itoa(data->exit_code);
			k = 0;
			while (str_exit_code[k])
				final_buffer[j++] = str_exit_code[k++];
			free(str_exit_code);
			i += 2;
		}
		else if ((str[i] == '$') && ((str[i + 1] == '\0') || (str[i + 1] == ' ') || (!ft_isalnum(str[i + 1]))))
			final_buffer[j++] = str[i++];
		else if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if ((str[i] == '$' && str[i + 1] != '$') || str[i] == 34)
		{
			// printf("%c\n", str[i]);
			i++;
			name_len = 0;
			while (ft_isalnum(str[i]) || str[i] == '_')
				name[name_len++] = str[i++];
			name[name_len] = '\0';
			value = ft_copy(ft_search_value(data->env, name));
			// printf("%s\n", value);
			if (!value)
				value = ft_copy("");
			k = 0;
			while (value[k])
				final_buffer[j++] = value[k++];
			free(value);
		}
		else
			final_buffer[j++] = str[i++];
	}
	final_buffer[j] = '\0';
	return (final_buffer);
}

void	expander(t_token *token, t_data	*data)
{
	t_token	*current;
	char	*new_value;

	current = token;
	while (current)
	{
		if (((current->type == WORD) || (current->type == DOUBLE_QUOTES)) && ft_strchr(current->value, '$'))
		{
			new_value = new_token_value(current->value, data);
			if (new_value)
			{
				free(current->value);
				current->value = new_value;
			}
		}
		// printf("Token apres expansion: %s\n", current->value);
		current = current->next;
	}
}


// test : echo "exit_code ->$? user ->$USER home -> $HOME" erreur car affiche ->$USER et pas ->naankour autre erreur $? doit afficher exit_code
// echo $?HELLO doit afficher exit_code suivi de HELLO
// echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" doit afficher le $ aussi
// echo $?HELLO

// $USER$USER oooook mais doit afficher "naankournaankour :command not found"
// $$USER oooook mais doit afficher "$naankour :command not found"



// $ tout seul doit afficher quoi ?
// $132 oooookkkk mais pas chiffre negatif
// echo "$$USER" ooookkkkk
// echo "$USER"oooooookkkk
// echo "$$USER\$USER""$USER" ooookkkk
// echo $USER "$USER$USER" $USER "$USER -n $USERecho $USER"$USER $USER" $USER" not ok manque un espace entre deux token par exemple echo "coucou" coucou cest bon okokokokokok
// Pre$USERPost
//Some$NOT_SETvalue

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $1
// naankour@c1r3p4:~/Documents/Minishellbis$ echo $123
// 23
// naankour@c1r3p4:~/Documents/Minishellbis$ echo $dfjkslkgfjsw
// naankour@c1r3p4:~/Documents/Minishellbis$ echo $658
// 58
