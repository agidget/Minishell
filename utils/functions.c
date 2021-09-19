/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:35 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:37 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_lstnew(char *key, char *value)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	malloc_error(new);
	if (new)
	{
		new->key = key;
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*old;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	old = *lst;
	while (old->next)
		old = old->next;
	new->next = NULL;
	old->next = new;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (-(unsigned char)s2[i]);
		if (s2[i] == '\0')
			return ((unsigned char)s1[i]);
		i++;
	}
	return (0);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = malloc(ft_strlen((char *)src) + 1);
	malloc_error(dest);
	ft_strcpy(dest, (char *)src);
	return (dest);
}
