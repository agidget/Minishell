/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:53 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:57:48 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*str;
	char	*cur_dir;

	str = malloc(sizeof(char) * 512);
	malloc_error(str);
	cur_dir = getcwd(str, 512);
	if (!cur_dir)
		ft_putstr_fd(strerror(errno), 2);
	return (cur_dir);
}

void	my_pwd(int out)
{
	char	*cur_dir;

	g_status = 0;
	cur_dir = get_pwd();
	ft_putstr_fd(cur_dir, out);
	free(cur_dir);
	ft_putchar_fd('\n', out);
}
