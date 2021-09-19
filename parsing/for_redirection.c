/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:28 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:30 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_for_redirection(char *str, int *j)
{
	int	flag;

	flag = 0;
	errno = 0;
	if (str[*j] == str[0])
	{
		*j += 1;
		flag = 1;
	}
	if (str[*j] == 32)
		*j += 1;
	return (flag);
}

void	one_redirect(t_list **main_struct, char *str, int j, char *file)
{
	if ((str - j)[0] == '>')
	{
		if ((*main_struct)->out != 1)
			close((*main_struct)->out);
		(*main_struct)->out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if ((str - j)[0] == '<')
	{
		if ((*main_struct)->in != 0)
			close((*main_struct)->in);
		(*main_struct)->in = open(file, O_RDONLY, 0644);
	}
}

char	*find_filename(char *str, int len, char redirect, int flag)
{
	int		len2;
	char	*file;

	if (flag == 2 && redirect == '<')
	{
		len2 = space_len(str + len, 32, 0);
		file = strcopy(str + len, len2);
	}
	else
		file = strcopy(str, len - 1);
	return (file);
}

void	create_temp_file(t_list **main_struct)
{
	if ((*main_struct)->temp_file != NULL)
	{
		unlink((*main_struct)->temp_file);
		free((*main_struct)->temp_file);
	}
	(*main_struct)->temp_file = malloc(sizeof(char) * 3);
	malloc_error((*main_struct)->temp_file);
	(*main_struct)->temp_file[0] = '.';
	(*main_struct)->temp_file[1] = '1';
	(*main_struct)->temp_file[2] = '\0';
}
