/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_env_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:29 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:41:30 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_nodes(t_envp **head, t_envp *a1)
{
	t_envp	*a0;
	t_envp	*a2;
	t_envp	*a3;

	a0 = *head;
	a2 = a1->next;
	a3 = a2->next;
	if (ft_strcmp((*head)->key, a1->key) != 0)
	{
		while (ft_strcmp(a0->next->key, a1->key) != 0)
			a0 = a0->next;
		a0->next = a2;
		a1->next = a3;
		a2->next = a1;
	}
	else
	{
		a1->next = a3;
		a2->next = a1;
		*head = a2;
	}
}

t_envp	*sorted_envp(char **envp)
{
	t_envp	*l2;
	t_envp	*head;
	t_envp	*my_env1;

	my_env1 = kv_env(envp);
	head = my_env1;
	while (my_env1)
	{
		l2 = head;
		while (l2->next != NULL)
		{
			if (ft_strcmp(l2->key, l2->next->key) > 0)
				swap_nodes(&head, l2);
			if (l2->next == NULL)
				break ;
			l2 = l2->next;
		}
		my_env1 = my_env1->next;
	}
	my_env1 = head;
	return (my_env1);
}

void	init_fab_env(t_fab_env **envv, char **envp)
{
	*envv = malloc(sizeof(t_fab_env));
	malloc_error(envv);
	(*envv)->orig_env = kv_env(envp);
	(*envv)->sorted_env = sorted_envp(envp);
}

void	del_fab_en(t_envp *en)
{
	t_envp	*tmp;

	if (!en)
		return ;
	while (en)
	{
		tmp = en->next;
		free(en->key);
		free(en->value);
		en = tmp;
	}
	free(tmp);
	free(en);
}

void	clear_fab_env(t_fab_env *envv)
{
	t_envp	*t1;
	t_envp	*t2;

	del_fab_en(envv->orig_env);
	del_fab_en(envv->sorted_env);
	while (envv->orig_env)
	{
		t1 = envv->orig_env->next;
		free(envv->orig_env);
		envv->orig_env = t1;
	}
	while (envv->sorted_env)
	{
		t2 = envv->sorted_env->next;
		free(envv->sorted_env);
		envv->sorted_env = t2;
	}
	free(envv);
}
