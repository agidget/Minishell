/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:50:01 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:50:03 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_echo(t_list **main_struct, char *str, int *j)
{
	char	*temp;

	if (ft_strncmp(str, " -n ", 4) == 0
		|| ft_strncmp(str, " -n\0", 4) == 0)
	{
		temp = ft_strjoin((*main_struct)->cmd, " -n");
		free((*main_struct)->cmd);
		(*main_struct)->cmd = temp;
		*j = *j + 3;
	}
}

void	create_first_arg(t_list **main_struct, char *str, int j)
{
	(*main_struct)->args = (t_arg *)malloc(sizeof(t_arg) * 1);
	malloc_error((*main_struct)->args);
	(*main_struct)->args->head = (*main_struct)->args;
	(*main_struct)->args->next = NULL;
	(*main_struct)->args->val = strcopy(str, j - 1);
}

void	create_arg(t_list **main_struct, char *str, int j)
{
	(*main_struct)->args->next = malloc(sizeof(t_arg));
	malloc_error((*main_struct)->args->next);
	(*main_struct)->args->next->head = (*main_struct)->args->head;
	(*main_struct)->args = (*main_struct)->args->next;
	(*main_struct)->args->val = strcopy(str, j - 1);
	(*main_struct)->args->next = NULL;
}

int	check_syntax_error(char *str)
{
	int		res;
	int		res2;
	char	*temp;

	res = ft_strchr(str, '<');
	res2 = ft_strchr(str, '>');
	if (res > res2)
		res = res2;
	temp = cut_str(str, 0, res);
	free(str);
	free(temp);
	print_syntax_error();
	return (258);
}

void	create_pipe(t_list **main_struct, int *i)
{
	(*main_struct)->next = init_main_struct();
	(*main_struct)->next->head = (*main_struct)->head;
	*main_struct = (*main_struct)->next;
	*i = *i + 1;
}
