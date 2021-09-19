/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:48:41 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:48:43 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_space_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i] == ' ')
	{
		len++;
		*i = *i + 1;
	}
	return (len);
}

int	if_space_in_quotes(char *str, int *i, char **temp_str)
{
	int		len;
	char	*temp;
	int		a;

	a = 0;
	temp = NULL;
	len = find_space_len(str, i);
	if (str[*i] == '\0')
		len++;
	else if (len <= 1)
		return (0);
	temp = malloc(sizeof(char) * (len));
	len--;
	while (a < len)
	{
		temp[a] = ' ';
		a++;
	}
	temp[a] = '\0';
	after_quotes(temp_str, temp);
	if_chars(temp_str, str + *i, i, NULL);
	return (1);
}

char	*init_variables(int *i, int *j, char *str)
{
	*i = 0;
	*j = (int)ft_strlen(str);
	return (NULL);
}

int	create_struct(t_list **main_struct, char *str)
{
	char	*temp_str;
	int		i;
	int		j;

	temp_str = init_variables(&i, &j, str);
	(*main_struct)->head = *main_struct;
	while (i < j)
	{
		if (str[i] == ' ')
			if_spaces(main_struct, &temp_str, str, &i);
		else if (str[i] == '|')
			if_pipe(main_struct, str, &i);
		else if (str[i] == '>' || str[i] == '<')
		{
			if (if_redirect(main_struct, str + i, &i) != 0)
			{
				if (temp_str != NULL)
					free(temp_str);
				return (1);
			}
		}
		else if (str[i] != ' ')
			in_struct(main_struct, str + i, &i, 0);
	}
	return (0);
}

t_list	*init_main_struct(void)
{
	t_list	*main_struct;

	main_struct = (t_list *)malloc(sizeof(t_list));
	malloc_error(main_struct);
	main_struct->cmd = NULL;
	main_struct->head = main_struct;
	main_struct->out = 1;
	main_struct->in = 0;
	main_struct->temp_file = NULL;
	main_struct->cmd_arr = NULL;
	main_struct->args = NULL;
	main_struct->next = NULL;
	return (main_struct);
}
