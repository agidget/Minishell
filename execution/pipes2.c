/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:42:12 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:58:32 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**for_fds(int **fd, int size)
{
	int	i;

	fd = malloc(sizeof(int *) * (size - 1));
	malloc_error(fd);
	i = 0;
	while (i < size - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		malloc_error(fd[i]);
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		if (pipe(fd[i]) == -1)
			ft_error(strerror(errno));
		i++;
	}
	return (fd);
}

t_pipes	*init_pipes(t_list *lst)
{
	int		size;
	t_pipes	*pip;

	size = ft_lstsize(lst);
	pip = malloc(sizeof(t_pipes));
	malloc_error(pip);
	pip->fd = for_fds(pip->fd, size);
	if (size == 1 && which_cmd(lst->cmd))
		pip->pid = NULL;
	else
	{
		pip->pid = malloc(sizeof(int) * size);
		malloc_error(pip->pid);
	}
	return (pip);
}

void	close_fds(t_list *lst)
{
	if (lst->out != 1)
		dup2(1, lst->out);
	if (lst->in != 0)
		close(lst->in);
	if (lst->temp_file)
		unlink(lst->temp_file);
	if (lst->out != 1)
		close(lst->out);
}

void	no_pipes_builtin(t_list *lst, t_fab_env *envv)
{
	built_in_commands(lst, envv);
	close_fds(lst);
}

void	no_pipes(t_pipes *pip, t_list *lst, t_fab_env *envv)
{
	int	sig;

	if (which_cmd(lst->cmd) == 1)
		no_pipes_builtin(lst, envv);
	else
	{
		pip->pid[0] = fork();
		sig_in_fork();
		if (pip->pid[0] == -1)
			print_fork_error();
		if (pip->pid[0] == 0)
		{
			dup2(lst->in, 0);
			dup2(lst->out, 1);
			close_fds(lst);
			define_path(lst, envv);
		}
		waitpid(pip->pid[0], &sig, 0);
		g_status = WEXITSTATUS(sig);
		if (!g_status && WIFSIGNALED(sig))
			g_status = 128 + WTERMSIG(sig);
	}
}
