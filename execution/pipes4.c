/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:42:21 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:58:48 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	for_end(t_pipes *pip, t_list *lst)
{
	int	i;
	int	size;
	int	sig;

	size = ft_lstsize(lst->head);
	i = -1;
	while (++i < size - 1)
	{
		close(pip->fd[i][0]);
		close(pip->fd[i][1]);
	}
	i = -1;
	while (++i < size)
		waitpid(pip->pid[i], &sig, 0);
	g_status = WEXITSTATUS(sig);
	if (!g_status && WIFSIGNALED(sig))
		g_status = 128 + WTERMSIG(sig);
}

void	with_pipes(t_pipes *pip, t_list *lst, t_fab_env *envv)
{
	int		i;
	t_list	*head;

	head = lst->head;
	i = 0;
	while (lst)
	{
		pip->pid[i] = fork();
		sig_in_fork();
		if (pip->pid[i] == -1)
			print_fork_error();
		if (pip->pid[i] == 0)
		{
			if (which_cmd(lst->cmd) == 1)
				with_pipes_builtin(pip, lst, envv, i);
			else
				with_pipes_execve(pip, lst, envv, i);
		}
		i++;
		lst = lst->next;
	}
	lst = head;
	for_end(pip, lst);
}

void	main_pipes(t_pipes *pip, t_list *lst, t_fab_env *envv)
{
	int	size;

	size = ft_lstsize(lst);
	if (size == 1)
		no_pipes(pip, lst, envv);
	else
		with_pipes(pip, lst, envv);
}
