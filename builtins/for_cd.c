/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:20 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:56:34 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	home_cd(t_fab_env **envv)
{
	t_envp	*head;

	head = (*envv)->orig_env;
	while ((*envv)->orig_env)
	{
		if (ft_strcmp((*envv)->orig_env->key, "HOME") == 0)
		{
			chdir((*envv)->orig_env->value);
			(*envv)->orig_env = head;
			return (1);
		}
		(*envv)->orig_env = (*envv)->orig_env->next;
	}
	(*envv)->orig_env = head;
	return (0);
}

void	my_cd(t_arg *args, int out, t_fab_env **envv)
{
	char	*cur_dir1;

	g_status = 0;
	if (!args)
	{
		if (home_cd(envv) == 0)
			cd_home_error();
		return ;
	}
	if (args->val[0] == '~' && args->val[1] == '\0')
		return ;
	if (args->val[0] == '-' && args->val[1] == '\0')
	{
		cd_oldpwd(out, envv);
		return ;
	}
	cur_dir1 = get_pwd();
	if (chdir(args->val) == -1)
	{
		my_cd_error(args->val);
		free(cur_dir1);
		return ;
	}
	part_my_cd(envv, cur_dir1);
}
