/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:40:52 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:41:02 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("Error with malloc\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	built_in_commands(t_list *main_struct, t_fab_env *envv)
{
	if (main_struct->args != NULL)
		main_struct->args = main_struct->args->head;
	if (ft_strcmp(main_struct->cmd, "echo") == 0)
		my_echo(main_struct->args, main_struct->out);
	else if (ft_strcmp(main_struct->cmd, "echo -n") == 0)
		my_echo_n(main_struct->args, main_struct->out);
	else if (ft_strcmp(main_struct->cmd, "pwd") == 0)
		my_pwd(main_struct->out);
	else if (ft_strcmp(main_struct->cmd, "export") == 0)
		my_export(&envv, &main_struct->args, main_struct->out);
	else if (ft_strcmp(main_struct->cmd, "unset") == 0)
		my_unset(&envv, main_struct->args);
	else if (ft_strcmp(main_struct->cmd, "cd") == 0)
		my_cd(main_struct->args, main_struct->out, &envv);
	else if (ft_strcmp(main_struct->cmd, "env") == 0)
		my_envp(main_struct->out, envv);
	else if (ft_strcmp(main_struct->cmd, "exit") == 0)
		my_exit(main_struct->args, main_struct);
	if (main_struct->args != NULL)
		main_struct->args = main_struct->args->head;
}

int	part_ex_check(char *val, int i, int flag)
{
	if (flag == 0)
	{
		if (!ft_isalpha_mod(val[i]) && !ft_isdigit(val[i]))
		{
			export_args_error(val);
			return (1);
		}
	}
	return (0);
}
