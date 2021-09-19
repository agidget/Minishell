/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_cd_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:09 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:41:10 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	for_change_oldpwd(char *cur_dir, t_envp *en)
{
	t_envp	*head;

	head = en;
	while (en)
	{
		if (ft_strncmp("OLDPWD", en->key, 6) == 0)
		{
			free(en->value);
			en->value = ft_strdup(cur_dir);
			en = head;
			return ;
		}
		en = en->next;
	}
	en = head;
}

void	change_oldpwd(char *cur_dir, t_fab_env **envv)
{
	for_change_oldpwd(cur_dir, (*envv)->orig_env);
	for_change_oldpwd(cur_dir, (*envv)->sorted_env);
}

void	for_change_pwd(char *cur_dir, t_envp *en)
{
	t_envp	*head;

	head = en;
	while (en)
	{
		if (ft_strncmp("PWD", en->key, 3) == 0)
		{
			free(en->value);
			en->value = ft_strdup(cur_dir);
			en = head;
			return ;
		}
		en = en->next;
	}
	en = head;
}

void	change_pwd(char *cur_dir, t_fab_env **envv)
{
	for_change_pwd(cur_dir, (*envv)->orig_env);
	for_change_pwd(cur_dir, (*envv)->sorted_env);
}

char	*get_oldpwd(t_fab_env *envv)
{
	t_envp	*head;
	char	*str;

	head = envv->orig_env;
	str = NULL;
	while (envv->orig_env)
	{
		if (ft_strncmp("OLDPWD", envv->orig_env->key, 6) == 0)
		{
			str = envv->orig_env->value;
			envv->orig_env = head;
			return (str);
		}
		envv->orig_env = envv->orig_env->next;
	}
	envv->orig_env = head;
	cd_home_error();
	return (NULL);
}
