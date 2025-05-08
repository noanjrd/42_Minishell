/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_from_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:28:00 by njard             #+#    #+#             */
/*   Updated: 2025/05/08 17:35:40 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(int c)
{
	if (((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z'))
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
int	ft_strlen(char *string)
{
	int i;

	i = 0;
	while(string[i])
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char *ft_join(char *s1, char *s2)
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
	new_string = malloc((i + j + 1) * sizeof(char));
	if (!new_string)
		return(NULL);
	i = 0;
	j = 0;
	while(s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = 0;
	return(new_string);
}

int	ft_strstr(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while(s1[i])
	{
		if (s1[i] == s2[0])
		{
			j = 1;
			while (s2[j])
			{
				if (s2[j] != s1[i + j])
					break;
				if (s2[j + 1] == '\0')
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

size_t	ft_strlcpy( char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
		{
			i++;
		}
		return (i);
	}
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	signe;

	i = 0;
	nb = 0;
	signe = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != '\0')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * signe);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}
