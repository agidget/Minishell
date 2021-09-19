/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:33 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:35 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_quote(char **temp_str, char *str, int *i)
{
	char	*new_string;
	int		j;

	new_string = NULL;
	j = 0;
	if (str[*i] == '\'')
	{
		j = j + *i + 1;
		while (str[j] != '\0' && str[j] != '\'')
		{
			add_char (&new_string, str[j]);
			j++;
		}
	}
	*i = j + 1;
	after_quotes(temp_str, new_string);
}

void	dollar_in_quotes(char **new_string, int *j, char *str, t_fab_env *envv)
{
	char	*temp;
	int		a;

	a = 0;
	temp = NULL;
	if (*new_string == NULL)
	{
		*new_string = dollar(str + *j, envv, &a);
		*j = *j + a - 1;
		a = 0;
	}
	else
	{
		temp = dollar(str + *j, envv, &a);
		*j = *j + a - 1;
		a = 0;
		free_join(new_string, temp);
		temp = NULL;
	}
}

void	double_quote(char **temp_str, char *str, int *i, t_fab_env *envv)
{
	char	*new_string;
	int		j;

	new_string = NULL;
	j = 0;
	j = j + *i + 1;
	while (str[j] != '\0' && str[j] != '\"')
	{
		if (str[j] == '$')
		{
			if (str[j + 1] == '\'' || str[j + 1] == '\"')
				add_char (&new_string, str[j]);
			else if (str[j + 1] == '\"')
				j++;
			else
				dollar_in_quotes(&new_string, &j, str, envv);
		}
		else
		{
			add_char (&new_string, str[j]);
		}
		j++;
	}
	*i = j + 1;
	after_quotes(temp_str, new_string);
}

void	if_quotes(char **temp_str, char *str, int *i, t_fab_env *envv)
{
	if (str[*i] == '\'')
		one_quote(temp_str, str, i);
	else
		double_quote(temp_str, str, i, envv);
}
