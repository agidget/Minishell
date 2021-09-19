/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:39 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 12:52:53 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i++])
		;
	return (i - 1);
}

char	*ft_strchr_mod(char *s, int c)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			str = ft_strdup((char *)s + i + 1);
			break ;
		}
		else
			i++;
	}
	if (c == '\0')
		str = ft_strdup((char *)s + ft_strlen(s));
	return (str);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalpha_mod(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
