/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:11 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:14 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *filename, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	printf("Error code: %d\n", errno);
}

void	free_cmd_array(t_list *main_struct)
{
	int	i;

	i = 0;
	while (main_struct->cmd_arr[i] != NULL)
	{
		free(main_struct->cmd_arr[i]);
		i++;
	}
	free(main_struct->cmd_arr);
}

void	free_cmd(t_list *main_struct)
{
	free((*main_struct).cmd);
	(*main_struct).cmd = NULL;
	if (main_struct->cmd_arr != NULL)
	{
		free_cmd_array(main_struct);
		main_struct->cmd_arr = NULL;
	}
	if (main_struct->temp_file != NULL)
	{
		unlink(main_struct->temp_file);
		free(main_struct->temp_file);
		main_struct->temp_file = NULL;
	}
}

void	free_args(t_list *main_struct)
{
	t_arg	*temp;

	main_struct->args = main_struct->args->head;
	while (main_struct->args != NULL)
	{
		temp = main_struct->args->next;
		if ((*main_struct).args->val != NULL)
			free((*main_struct).args->val);
		free(main_struct->args);
		main_struct->args = NULL;
		main_struct->args = temp;
	}
}

void	free_all(t_list *main_struct)
{
	t_list	*temp2;

	if (main_struct->head != NULL)
		main_struct = main_struct->head;
	while (main_struct != NULL)
	{
		temp2 = main_struct->next;
		if ((*main_struct).cmd != NULL)
			free_cmd(main_struct);
		if (main_struct->args != NULL)
			free_args(main_struct);
		free(main_struct);
		main_struct = temp2;
	}
}
