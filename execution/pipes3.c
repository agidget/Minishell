/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:42:16 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:42:17 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_pipe(t_pipes *pip, t_list *lst, int size)
{
	int	i;

	close(pip->fd[0][0]);
	i = 0;
	while (++i < size - 1)
	{
		close(pip->fd[i][0]);
		close(pip->fd[i][0]);
	}
	dup2(lst->in, 0);
	if (lst->out == 1)
		dup2(pip->fd[0][1], 1);
	else
		dup2(lst->out, 1);
	close(pip->fd[0][1]);
}

void	middle_pipe(t_pipes *pip, t_list *lst, int i, int size)
{
	int	j;

	j = -1;
	while (++j < size - 1)
	{
		if (j != i - 1)
			close(pip->fd[j][0]);
		if (j != i)
			close(pip->fd[j][1]);
	}
	if (lst->in == 0)
		dup2(pip->fd[i - 1][0], 0);
	else
		dup2(lst->in, 0);
	if (lst->out == 1)
		dup2(pip->fd[i][1], 1);
	else
		dup2(lst->out, 1);
	close(pip->fd[i - 1][0]);
	close(pip->fd[i][1]);
}

void	last_pipe(t_pipes *pip, t_list *lst, int size)
{
	int	i;

	close(pip->fd[size - 2][1]);
	i = -1;
	while (++i < size - 2)
	{
		close(pip->fd[i][0]);
		close(pip->fd[i][1]);
	}
	if (lst->in == 0)
		dup2(pip->fd[size - 2][0], 0);
	else
		dup2(lst->in, 0);
	dup2(lst->out, 1);
	close(pip->fd[size - 2][0]);
}

void	with_pipes_builtin(t_pipes *pip, t_list *lst, t_fab_env *envv, int i)
{
	int	size;

	size = ft_lstsize(lst->head);
	if (i == 0)
		first_pipe(pip, lst, size);
	else if (i == size - 1)
		last_pipe(pip, lst, size);
	else
		middle_pipe(pip, lst, i, size);
	if (lst->in != 0)
		close(lst->in);
	if (lst->temp_file)
		unlink(lst->temp_file);
	if (lst->out != 1)
		close(lst->out);
	built_in_commands(lst, envv);
	exit(errno);
}

void	with_pipes_execve(t_pipes *pip, t_list *lst, t_fab_env *envv, int i)
{
	int	size;

	size = ft_lstsize(lst->head);
	if (i == 0)
		first_pipe(pip, lst, size);
	else if (i == size - 1)
		last_pipe(pip, lst, size);
	else
		middle_pipe(pip, lst, i, size);
	if (lst->in != 0)
		close(lst->in);
	if (lst->temp_file)
		unlink(lst->temp_file);
	if (lst->out != 1)
		close(lst->out);
	define_path(lst, envv);
}
