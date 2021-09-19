/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:42 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:43 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_j(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '$' && str[i] != 9 && str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

int	if_chars_copy(char *str, char **temp, int j)
{
	int		i;
	char	*copy;

	copy = malloc(sizeof(char) * (j + 1));
	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\''
		&& str[i] != '\"' && str[i] != 9 && str[i] != '$'
		&& str[i] != '<' && str[i] != '>')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	*temp = ft_strdup(copy);
	free(copy);
	return (i);
}

void	if_chars(char **temp_str, char *str, int *i, t_fab_env *envv)
{
	char	*temp;
	int		j;

	j = 0;
	temp = NULL;
	if (str[j] == '$')
		temp = dollar(str + j, envv, &j);
	else
	{
		j = j + count_j(str);
		j = if_chars_copy(str, &temp, j);
	}
	if (str[j] != '\0' && str[j] != ' ' && str[j] != '\''
		&& str[j] != '\"' && str[j] != 9 && str[j] != '$'
		&& str[j] != '<' && str[j] != '>')
	{
		*i = *i + j;
		after_quotes(temp_str, temp);
		return ;
	}
	*i = *i + j;
	after_quotes(temp_str, temp);
}

void	if_redir_in_str(char *str, char **temp_str, int *i)
{
	char	*temp;
	int		len;
	int		j;

	j = 0;
	len = 1;
	if (*i != 0 && str[*i - 1] != 32)
		if_space(str, temp_str, i);
	if (str[*i + 1] == str[*i])
		len++;
	temp = malloc(sizeof(char) * (len + 1));
	malloc_error(temp);
	temp[j] = str[*i];
	j++;
	if (str[*i] == str[*i + 1])
	{
		temp[j] = str[*i];
		j++;
	}
	temp[j] = '\0';
	if (*i == 0 || temp_str == NULL)
		*temp_str = temp;
	else
		free_join(temp_str, temp);
	*i = *i + len;
}

char	*main_parser(char *str, t_fab_env *envv)
{
	char	*temp_str;
	int		i;
	int		j;

	i = 0;
	j = (int)ft_strlen(str);
	temp_str = NULL;
	while (i < j)
	{
		if (str[i] == '<' || str[i] == '>')
			if_redir_in_str(str, &temp_str, &i);
		if (str[i] == ' ' || str[i] == 9 || str[j] == 11)
			if_space(str, &temp_str, &i);
		if (str[i] == '\'' || str[i] == '\"')
			if_quotes(&temp_str, str, &i, envv);
		else if (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
		{
			if (temp_str == NULL)
				if_chars(&temp_str, str + i, &i, envv);
			else
				if_chars(&temp_str, str + i, &i, envv);
		}
	}
	return (temp_str);
}
