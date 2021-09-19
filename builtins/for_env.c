/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:32 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:57:02 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_envp(t_fab_env *envv, t_envp *head)
{
	while (envv->orig_env)
	{
		if (ft_strcmp(envv->orig_env->key, "PATH") == 0)
		{
			envv->orig_env = head;
			break ;
		}
		envv->orig_env = envv->orig_env->next;
	}
}

void	my_envp(int out, t_fab_env *envv)
{
	t_envp	*head;

	g_status = 0;
	head = envv->orig_env;
	check_envp(envv, head);
	if (envv->orig_env == NULL)
	{
		no_file("env");
		envv->orig_env = head;
		return ;
	}
	while (envv->orig_env)
	{
		ft_putstr_fd(envv->orig_env->key, out);
		ft_putchar_fd('=', out);
		ft_putstr_fd(envv->orig_env->value, out);
		ft_putchar_fd('\n', out);
		envv->orig_env = envv->orig_env->next;
	}
	envv->orig_env = head;
	return ;
}
