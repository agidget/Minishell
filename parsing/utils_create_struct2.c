/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_struct2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:07 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:08 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_spaces(t_list **main_struct, char **temp_str, char *str, int *i)
{
	if (if_space_in_quotes(str, i, temp_str) == 1)
	{
		if ((*main_struct)->args == NULL)
			create_first_arg(main_struct, *temp_str, ft_strlen(*temp_str));
		else
			create_arg(main_struct, *temp_str, ft_strlen(*temp_str));
		free(*temp_str);
		*temp_str = NULL;
	}
}

void	if_pipe(t_list **main_struct, char *str, int *i)
{
	if (str[*i + 1] == '|')
		in_struct(main_struct, str + *i, i, 1);
	else
		create_pipe(main_struct, i);
}

int	if_redirects(t_list **main_struct, char *str, char **temp_str, int i)
{
	if (if_redirect(main_struct, str + i, &i) != 0)
	{
		if (*temp_str != NULL)
			free(*temp_str);
		return (1);
	}
	return (0);
}

void	in_struct(t_list **main_struct, char *str, int *i, int flag)
{
	int	j;

	j = space_len(str, 32, flag);
	if ((*main_struct)->cmd == NULL)
	{
		(*main_struct)->cmd = strcopy(str, j - 1);
		if (ft_strncmp((*main_struct)->cmd, "echo", 4) == 0)
			if_echo(main_struct, str + 4, i);
	}
	else
	{
		if ((*main_struct)->args == NULL)
			create_first_arg(main_struct, str, j);
		else
			create_arg(main_struct, str, j);
	}
	*i = *i + j;
}
