/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:21 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:23 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_str(char *str, int i, int j)
{
	int		a;
	char	*key;

	a = 0;
	key = malloc(sizeof(char) * (j - i + 1));
	malloc_error(key);
	while (i < j)
	{
		key[a] = str[i];
		a++;
		i++;
	}
	key[a] = '\0';
	return (key);
}

void	create_strings_for_quotes(char **temp, char **temp2, char **new_string)
{
	if (*new_string != NULL)
	{
		*temp = ft_strdup(*new_string);
		*temp2 = malloc(sizeof(char) * (ft_strlen(*new_string) + 1));
		malloc_error(*temp2);
		free(*new_string);
	}
	else
	{
		*temp2 = malloc(sizeof(char) * 2);
		malloc_error(*temp2);
	}
}

void	add_char(char **new_string, char c)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	temp = NULL;
	create_strings_for_quotes(&temp, &temp2, new_string);
	if (temp != NULL)
	{
		while (temp[i] != '\0')
		{
			temp2[i] = temp[i];
			i++;
		}
		free(temp);
	}
	temp2[i] = c;
	i++;
	temp2[i] = '\0';
	*new_string = ft_strdup(temp2);
	free(temp2);
}

void	after_quotes(char **temp_str, char *new_string)
{
	if (new_string != NULL)
	{
		if (*temp_str == NULL)
		{
			*temp_str = ft_strdup(new_string);
			free(new_string);
		}
		else
			free_join(temp_str, new_string);
	}
}
