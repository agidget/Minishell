/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_pars2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:17 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:18 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_spaces(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9 && str[i] != 11)
			return (1);
		i++;
	}
	return (0);
}

void	if_space(char *str, char **temp_str, int *i)
{
	char	*space;

	if (check_spaces(str, *i) != 0)
	{
		space = malloc(sizeof(char) * 2);
		malloc_error(space);
		space[0] = ' ';
		space[1] = '\0';
		if (*temp_str != NULL)
			free_join(temp_str, space);
		else
		{
			*temp_str = ft_strdup(space);
			free(space);
		}
		while (str[*i] == ' ' || str[*i] == 9 || str[*i] == 11)
			*i = *i + 1;
	}
	else
		*i = *i + 1;
}

void	free_join(char **temp_str, char *new_string)
{
	char	*temp;

	temp = ft_strjoin(*temp_str, new_string);
	free(*temp_str);
	*temp_str = temp;
	free(new_string);
	new_string = NULL;
}

int	space_len(char *str, char c, int flag)
{
	int	i;

	i = 0;
	if (flag != 0)
	{
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	else
	{
		while (str[i] != c && str[i] != '\0' && str[i] != '|')
			i++;
	}
	return (i);
}

char	*strcopy(char *source, int i)
{
	char	*dest;
	int		a;

	dest = (char *)malloc(sizeof(char) * (i + 1));
	malloc_error(dest);
	a = 0;
	while (a <= i)
	{
		dest[a] = source[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}
