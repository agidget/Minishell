/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:57 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:57:58 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_el_env(t_envp *en_prev)
{
	t_envp	*tmp;

	if (en_prev->next->next)
		tmp = en_prev->next->next;
	free(en_prev->next->key);
	free(en_prev->next->value);
	free(en_prev->next);
	if (en_prev->next->next)
		en_prev->next = tmp;
	else
		en_prev->next = NULL;
}

void	del_first_env(t_envp *en)
{
	t_envp	*head;
	t_envp	*tmp;

	head = en;
	tmp = en->next;
	free(en->key);
	free(en->value);
	free(en);
	head = tmp;
}

int	unset_check_args(char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (i == 0 && !ft_isalpha_mod(val[i]))
		{
			unset_args_error(val);
			return (1);
		}
		if (!ft_isalpha_mod(val[i]) && !ft_isdigit(val[i]))
		{
			unset_args_error(val);
			return (1);
		}
		i++;
	}
	return (0);
}

void	my_unset_one_list(t_envp *en, t_arg *args)
{
	t_envp	*head;

	head = en;
	while (en)
	{
		if (ft_strcmp(en->key, args->val) == 0)
		{
			del_first_env(en);
			return ;
		}
		if (en->next && ft_strcmp(en->next->key, args->val) == 0)
		{
			del_el_env(en);
			break ;
		}
		en = en->next;
	}
	en = head;
}

void	my_unset(t_fab_env **envv, t_arg *args)
{
	g_status = 0;
	if (!args)
		return ;
	while (args)
	{
		if (unset_check_args(args->val) == 0)
		{
			my_unset_one_list((*envv)->sorted_env, args);
			my_unset_one_list((*envv)->orig_env, args);
		}
		args = args->next;
	}
}
