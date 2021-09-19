/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:42 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 12:52:48 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_check_args(char *val)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (val[i])
	{
		if (i == 0 && !ft_isalpha_mod(val[i]))
		{
			export_args_error(val);
			return (1);
		}
		if (val[i] == '=')
		{
			flag = 1;
			i++;
		}
		if (part_ex_check(val, i, flag) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	export_print(t_envp *env1, int out)
{
	t_envp	*head;

	head = env1;
	while (env1)
	{
		ft_putstr_fd("declare -x ", out);
		ft_putstr_fd(env1->key, out);
		if (env1->value)
		{
			ft_putstr_fd("=\"", out);
			ft_putstr_fd(env1->value, out);
			ft_putchar_fd('"', out);
		}
		ft_putchar_fd('\n', out);
		env1 = env1->next;
	}
	env1 = head;
}

void	one_list_kv(t_envp *en, char *arg_key, char *arg_value)
{
	while (1)
	{
		if (ft_strcmp(en->key, arg_key) == 0)
		{
			if (arg_value)
			{
				free(en->value);
				en->value = ft_strdup(arg_value);
			}
			break ;
		}
		if (en->next == NULL)
		{
			en->next = malloc(sizeof(t_envp));
			en->next->key = ft_strdup(arg_key);
			if (arg_value)
				en->next->value = ft_strdup(arg_value);
			else
				en->next->value = NULL;
			en->next->next = NULL;
			break ;
		}
		en = en->next;
	}
}

void	for_change_kv(t_fab_env **envv, t_arg **args)
{
	t_envp	*head_orig;
	t_envp	*head_sort;
	char	*arg_key;
	char	*arg_value;

	arg_key = oppos_strchr_mod((*args)->val, '=');
	arg_value = ft_strchr_mod((*args)->val, '=');
	head_sort = (*envv)->sorted_env;
	head_orig = (*envv)->orig_env;
	one_list_kv((*envv)->sorted_env, arg_key, arg_value);
	(*envv)->sorted_env = head_sort;
	one_list_kv((*envv)->orig_env, arg_key, arg_value);
	(*envv)->orig_env = head_orig;
	free(arg_key);
	free(arg_value);
}

void	my_export(t_fab_env **envv, t_arg **args, int out)
{
	t_arg	*head_arg;

	g_status = 0;
	if (!(*args))
	{
		export_print((*envv)->sorted_env, out);
		return ;
	}
	head_arg = *args;
	while (*args)
	{
		if (export_check_args((*args)->val) == 0)
			for_change_kv(envv, args);
		*args = (*args)->next;
	}
	*args = head_arg;
}
