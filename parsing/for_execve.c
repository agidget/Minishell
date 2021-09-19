/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:24 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:25 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_lst(t_arg *args)
{
	int		size;
	t_arg	*temp;

	size = 0;
	temp = args;
	while (args != NULL)
	{
		args = args->next;
		size++;
	}
	args = temp;
	return (size);
}

int	check_empty(char *val, char **new)
{
	if (ft_strcmp(val, "\0") == 0)
	{
		*new = NULL;
		return (1);
	}
	return (0);
}

char	**create_args_array(t_list	*main_struct)
{
	char	**array;
	int		len;
	int		i;
	t_arg	*temp;

	i = 1;
	if (main_struct->args != NULL)
		main_struct->args = main_struct->args->head;
	len = size_of_lst(main_struct->args) + 2;
	array = malloc(sizeof(char *) * len);
	malloc_error(array);
	array[len - 1] = NULL;
	temp = main_struct->args;
	array[0] = ft_strdup(main_struct->cmd);
	while (main_struct->args != NULL)
	{
		if (check_empty(main_struct->args->val, &array[i]) == 1)
			break ;
		array[i] = ft_strdup(main_struct->args->val);
		main_struct->args = main_struct->args->next;
		i++;
	}
	main_struct->args = temp;
	return (array);
}
