/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:43 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:45 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*head;
	int		num;

	head = lst;
	num = 0;
	while (lst)
	{
		num++;
		lst = lst->next;
	}
	lst = head;
	return (num);
}

char	*ft_strjoin_mod(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if ((!s1 && !s2) || !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	str[i] = c;
	i++;
	j = -1;
	while (++j < ft_strlen(s2))
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin_orig(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if ((!s1 && !s2) || !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	j = -1;
	while (++j < ft_strlen(s2))
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}
