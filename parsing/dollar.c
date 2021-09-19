/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:48:46 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:58:58 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*if_question(char *str, int *a)
{
	int		j;
	char	*res;

	j = 2;
	while (str[j] == '?')
		j++;
	*a = *a + j - 1;
	j -= 2;
	if (j == 0)
		res = ft_itoa(g_status);
	else
		return (if_many_questions(j));
	return (res);
}

char	*one_dollar(void)
{
	char	*res;

	res = malloc(sizeof(char) * 10);
	malloc_error(res);
	res[0] = '$';
	res[1] = '\0';
	return (res);
}

char	*after_dollar(char *str, t_fab_env	*envv)
{
	int		j;
	char	*begin;
	char	*temp;

	j = 1;
	while (((str[j] >= 48 && str[j] <= 57) || (str[j] >= 65 && str[j] <= 90)
			|| (str[j] >= 96 && str[j] <= 122)))
		j++;
	begin = cut_str(str, 1, j);
	temp = envp_value(begin, envv);
	free(begin);
	if (temp == NULL)
	{
		temp = malloc(sizeof(char) * 2);
		malloc_error(temp);
		temp[0] = '\0';
	}
	return (temp);
}

char	*several_dollars(char *str, int *a)
{
	int		i;
	int		j;
	char	*res;

	j = 1;
	i = 0;
	while (str[j] == '$')
		j++;
	*a += j - 1;
	res = malloc(sizeof(char) * j);
	malloc_error(res);
	while (i < j)
	{
		res[i] = '$';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*dollar(char *str, t_fab_env	*envv, int *a)
{
	char	*res;
	int		i;

	i = 0;
	*a += 1;
	res = NULL;
	while (((str[*a] >= 48 && str[*a] <= 57) || (str[*a] >= 65 && str[*a] <= 90)
			|| (str[*a] >= 96 && str[*a] <= 122)))
		*a += 1;
	if (str[i + 1] == '\'' || str[i + 1] == '\"')
	{
		if_quotes(&res, str, a, envv);
		return (res);
	}
	if (str[i + 1] == 32 || str[i + 1] == 9 || str[i + 1] == 11
		|| str[i + 1] == '\0')
		return (one_dollar());
	else if (str[i + 1] == '?')
		return (if_question(str, a));
	else if (str[i + 1] == '$')
		return (several_dollars(str, a));
	else
		return (after_dollar(str, envv));
}
