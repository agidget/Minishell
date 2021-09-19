/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shell_level.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:48:37 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:48:39 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_value(char **value, char *str)
{
	free(*value);
	*value = ft_strdup(str);
}

void	error_shell_lvl(int lvl)
{
	static int	flag = 0;

	if (flag == 0)
	{
		ft_putstr_fd("warning: shell level (", 2);
		ft_putnbr_fd(lvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		flag++;
	}
	else
		flag = 0;
}

void	for_change_lvl(char **value)
{
	char	*str;
	int		level;

	level = ft_atoi(*value) + 1;
	if (level == 1000)
		replace_value(value, "\0");
	else if (level > 1000)
	{
		error_shell_lvl(level);
		replace_value(value, "1");
	}
	else
	{
		str = ft_itoa(level);
		replace_value(value, str);
		free(str);
	}
}

void	change_lvl(t_envp	*env)
{
	t_envp	*temp;

	temp = env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			if (env->value[0] == '\0')
			{
				replace_value(&env->value, "1");
				break ;
			}
			else
				for_change_lvl(&env->value);
			break ;
		}
		env = env->next;
	}
	env = temp;
}

void	change_shell_lvl(t_fab_env **env)
{
	change_lvl((*env)->orig_env);
	change_lvl((*env)->sorted_env);
}
