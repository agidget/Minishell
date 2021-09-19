/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:42:04 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:58:06 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*oppos_strchr(char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (!s[i])
		return (NULL);
	str = malloc(sizeof(char) * i + 1);
	malloc_error(str);
	i = 0;
	while (s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*oppos_strchr_mod(char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == '\0')
		return (ft_strdup(s));
	str = malloc(sizeof(char) * i + 1);
	malloc_error(str);
	i = 0;
	while (s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*for_free(char **new)
{
	size_t	i;

	i = 0;
	while (new[i])
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (NULL);
}

t_envp	*kv_env(char **envp)
{
	t_envp	*my_env;
	int		i;

	my_env = NULL;
	i = -1;
	while (envp[++i])
		ft_lstadd_back(&my_env, ft_lstnew(oppos_strchr(envp[i], '='),
				ft_strchr_mod(envp[i], '=')));
	return (my_env);
}

char	*envp_value(char *key, t_fab_env *envv)
{
	t_envp	*head;
	char	*str;

	head = envv->orig_env;
	str = NULL;
	if (ft_strcmp(key, "?") == 0)
	{
		str = ft_itoa(g_status);
		return (str);
	}
	while (envv->orig_env)
	{
		if (ft_strcmp(key, envv->orig_env->key) == 0)
		{
			str = ft_strdup(envv->orig_env->value);
			break ;
		}
		envv->orig_env = envv->orig_env->next;
	}
	envv->orig_env = head;
	return (str);
}
