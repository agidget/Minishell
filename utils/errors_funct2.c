/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_funct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:31 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:59:59 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_fork_error(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("fork failed\n", 2);
	g_status = 1;
	exit(g_status);
}

void	cd_home_error(void)
{
	ft_putstr_fd("cd: HOME not set\n", 2);
	g_status = 1;
}

void	my_cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	g_status = 1;
}

void	export_args_error(char *val)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(val, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
}

void	unset_args_error(char *val)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(val, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
}
