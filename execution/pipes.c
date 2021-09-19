/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:42:07 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:58:14 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	g_status = errno;
	exit(errno);
}

int	which_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "echo -n") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	*for_free_int(int **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	free_pipes(t_pipes *pip, t_list *lst)
{
	int	size;

	size = ft_lstsize(lst->head);
	for_free_int(pip->fd, size - 1);
	free(pip->pid);
	free(pip);
}
