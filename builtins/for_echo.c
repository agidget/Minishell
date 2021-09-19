/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:41:25 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:56:52 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*one_arg(t_arg *list)
{
	char	*str;
	char	*temp;

	str = NULL;
	while (list)
	{
		if (str)
		{
			if (list->next == NULL && check_spaces(list->val, 0) == 0)
				str = ft_strjoin_orig(str, list->val);
			else
			{
				temp = ft_strdup(str);
				free(str);
				str = ft_strjoin_mod(temp, list->val, ' ');
				free(temp);
			}
		}
		else
			str = ft_strjoin_mod(str, list->val, ' ');
		list = list->next;
	}
	return (str);
}

void	my_echo(t_arg *args, int out)
{
	char	*str;

	g_status = 0;
	str = NULL;
	if (!args)
		ft_putchar_fd('\n', out);
	else
	{
		str = one_arg(args);
		ft_putstr_fd(str, out);
		free(str);
		ft_putchar_fd('\n', out);
	}
}

void	my_echo_n(t_arg *args, int out)
{
	char	*str;

	g_status = 0;
	str = NULL;
	if (!args)
		return ;
	else
	{
		str = one_arg(args);
		ft_putstr_fd(str, out);
		free(str);
	}
}
