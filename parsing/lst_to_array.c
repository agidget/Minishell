/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:38 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:39 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
}

char	**lst_to_array(t_envp	*orig_env)
{
	int		len;
	int		i;
	char	**array;

	i = 0;
	len = size_of_envp(orig_env);
	array = malloc(sizeof(char *) * len + 1);
	while (orig_env != NULL)
	{
		array[i] = ft_strjoin_slash(orig_env->key, orig_env->value, '=');
		i++;
		orig_env = orig_env->next;
	}
	array[i] = NULL;
	return (array);
}
