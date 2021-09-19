/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:52 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:59 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 32 || str[i] == '\t')
			j++;
		i++;
	}
	if (i == 0)
		return (1);
	if (j == i)
		return (1);
	return (0);
}

int	check_args(t_list *main_struct)
{
	if (main_struct->args != NULL)
	{
		main_struct->args = main_struct->args->head;
		while (main_struct->args != NULL)
		{
			if (ft_strchr((*main_struct).args->val, '<') != -1
				|| ft_strchr((*main_struct).args->val, '>') != -1)
			{
				print_error((*main_struct).args->val, "syntax error");
				return (258);
			}
			if (main_struct->args->next == NULL)
				break ;
			else
				main_struct->args = main_struct->args->next;
		}
		main_struct->args = main_struct->args->head;
	}
	return (0);
}

int	commands(t_list *main_struct, t_fab_env	*envv)
{
	t_pipes		*pip;
	t_list		*temp;

	temp = main_struct->head;
	while (main_struct != NULL)
	{
		main_struct->cmd_arr = create_args_array(main_struct);
		main_struct = main_struct->next;
	}
	main_struct = temp;
	if (ft_strcmp(main_struct->cmd_arr[0], "minishell") == 0)
		change_shell_lvl(&envv);
	pip = init_pipes(main_struct);
	main_pipes(pip, main_struct, envv);
	free_pipes(pip, main_struct);
	return (0);
}

void	void_arg(int argc, char **argv)
{
	int		i;
	char	**temp;

	i = argc;
	temp = argv;
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*main_struct;
	t_fab_env	*envv;

	void_arg(argc, argv);
	rl_outstream = stderr;
	init_fab_env(&envv, envp);
	signals();
	while (1)
	{
		str = readline(MSH);
		if (str[0] != '\0')
		{
			add_history(str);
			main_struct = init_main_struct();
			if (parser(&main_struct, str, envv) == 0
				&& main_struct->cmd != NULL)
				commands(main_struct, envv);
			if (main_struct->args != NULL)
				main_struct->args = main_struct->args->head;
			free_all(main_struct);
		}
		free (str);
	}
}
