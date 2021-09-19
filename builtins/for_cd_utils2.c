/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cd_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:14 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:41:16 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	for_cd_oldpwd_en_part(char *my_oldpwd, t_envp *my_env)
{
	t_envp	*head;

	head = my_env;
	while (my_env)
	{
		if (ft_strncmp("PWD", my_env->key, 3) == 0)
		{
			free(my_env->value);
			my_env->value = ft_strdup(my_oldpwd);
			break ;
		}
		my_env = my_env->next;
	}
	my_env = head;
}

void	for_cd_oldpwd_en(char *my_pwd, char *my_oldpwd, t_envp *my_env, int f)
{
	t_envp	*head;

	for_cd_oldpwd_en_part(my_oldpwd, my_env);
	head = my_env;
	while (my_env)
	{
		if (ft_strncmp("OLDPWD", my_env->key, 6) == 0)
		{
			if (f == 1)
				free(my_env->value);
			my_env->value = ft_strdup(my_pwd);
			break ;
		}
		my_env = my_env->next;
	}
	my_env = head;
}

void	cd_oldpwd_env(char *my_pwd, char *my_oldpwd, t_fab_env **envv)
{
	int	flag;

	flag = 0;
	for_cd_oldpwd_en(my_pwd, my_oldpwd, (*envv)->orig_env, flag);
	flag = 1;
	for_cd_oldpwd_en(my_pwd, my_oldpwd, (*envv)->sorted_env, flag);
}

void	cd_oldpwd(int out, t_fab_env **envv)
{
	char	*my_pwd;
	char	*my_oldpwd;

	my_pwd = get_pwd();
	my_oldpwd = get_oldpwd(*envv);
	if (!my_oldpwd)
		return ;
	chdir(my_oldpwd);
	ft_putstr_fd(my_oldpwd, out);
	ft_putchar_fd('\n', out);
	cd_oldpwd_env(my_pwd, my_oldpwd, envv);
	free(my_pwd);
	free(my_oldpwd);
}

void	part_my_cd(t_fab_env **envv, char *cur_dir1)
{
	char	*cur_dir2;

	change_oldpwd(cur_dir1, envv);
	cur_dir2 = get_pwd();
	change_pwd(cur_dir2, envv);
	free(cur_dir1);
	free(cur_dir2);
}
