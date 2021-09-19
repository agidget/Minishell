/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:50 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:57:41 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**for_path(t_fab_env *envv)
{
	char	**paths;
	t_envp	*head;

	paths = NULL;
	head = envv->orig_env;
	while (envv->orig_env)
	{
		if (ft_strcmp(envv->orig_env->key, "PATH") == 0)
		{
			paths = ft_split(envv->orig_env->value, ':');
			break ;
		}
		envv->orig_env = envv->orig_env->next;
	}
	envv->orig_env = head;
	return (paths);
}

int	size_of_envp(t_envp	*env)
{
	int		size;
	t_envp	*temp;

	size = 0;
	temp = env;
	while (env != NULL)
	{
		env = env->next;
		size++;
	}
	env = temp;
	return (size);
}

char	**lst_to_ar(t_fab_env *envv)
{
	int		len;
	int		i;
	char	**a;
	t_envp	*head;

	i = 0;
	len = size_of_envp(envv->orig_env);
	a = malloc(sizeof(char *) * (len + 1));
	head = envv->orig_env;
	while (envv->orig_env)
	{
		a[i] = ft_strjoin_mod(envv->orig_env->key, envv->orig_env->value, '=');
		i++;
		envv->orig_env = envv->orig_env->next;
	}
	a[i] = NULL;
	envv->orig_env = head;
	return (a);
}

void	define_path(t_list *list, t_fab_env *envv)
{
	char	**paths;
	int		i;
	char	*path;
	char	**my_env;

	g_status = 0;
	if ((ft_strcmp(list->cmd_arr[0], "minishell") == 0)
		|| (ft_strcmp(list->cmd_arr[0], "./minishell") == 0))
		change_shell_lvl(&envv);
	my_env = lst_to_ar(envv);
	execve(list->cmd_arr[0], list->cmd_arr, my_env);
	paths = for_path(envv);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_mod(paths[i], list->cmd_arr[0], '/');
		execve(path, list->cmd_arr, my_env);
		free(path);
		i++;
	}
	for_free(paths);
	for_free(my_env);
	command_not_found(list->cmd_arr[0]);
	exit(127);
}
