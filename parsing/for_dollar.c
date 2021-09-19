/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:20 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:21 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*if_many_questions(int j)
{
	char	*temp2;
	char	*res;
	char	*temp;

	temp = ft_itoa(errno);
	temp2 = malloc(sizeof(char) * (j + 1));
	malloc_error(temp2);
	temp2[j] = '\0';
	j--;
	while (j >= 0)
	{
		temp2[j] = '?';
		j--;
	}
	res = ft_strjoin(temp, temp2);
	free(temp2);
	free(temp);
	return (res);
}
