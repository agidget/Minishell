/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:48 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:50 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparser_pipes(char *str)
{
	int		i;
	t_flags	prepars;

	i = 0;
	prepars.flag = 0;
	prepars.pipes = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != 9)
			prepars.flag++;
		if (str[i] == '|' && prepars.flag == 0)
			return (print_syntax_error());
		if (prepars.pipes > 0 && str[i] != '\0' && str[i] != '|'
			&& str[i] != '\'' && str[i] != '\"')
			prepars.pipes = 0;
		if (str[i] == '|')
			prepars.pipes++;
		i++;
	}
	if (prepars.pipes > 0)
		return (print_syntax_error());
	return (0);
}

int	preparser_quotes(char *str)
{
	int		i;
	t_flags	prepars;

	prepars.quote1 = 0;
	prepars.quote2 = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && prepars.quote2 != 1)
		{
			prepars.quote1++;
			if (prepars.quote1 == 2)
				prepars.quote1 = 0;
		}
		if (str[i] == '\"' && prepars.quote1 != 1)
		{
			prepars.quote2++;
			if (prepars.quote2 == 2)
				prepars.quote2 = 0;
		}
		i++;
	}
	if (prepars.quote2 != 0 || prepars.quote1 != 0)
		return (print_syntax_error());
	return (0);
}

int	preparser(char *str)
{
	if (preparser_pipes(str) != 0)
		return (1);
	if (preparser_quotes(str) != 0)
		return (1);
	return (0);
}

int	parser(t_list **main_struct, char *str, t_fab_env *envv)
{
	int		error;
	char	*temp_str;

	if (preparser(str) != 0)
		return (1);
	if (check_str(str) != 0)
		return (1);
	temp_str = main_parser(str, envv);
	if (preparser_pipes(str) != 0 || temp_str == NULL)
	{
		free(temp_str);
		return (1);
	}
	error = create_struct(main_struct, temp_str);
	if (error != 0)
	{
		free(temp_str);
		errno = error;
		return (error);
	}
	free(temp_str);
	(*main_struct) = (*main_struct)->head;
	if (check_args(*main_struct) != 0)
		return (1);
	return (0);
}
