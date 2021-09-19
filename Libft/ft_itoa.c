/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:43:46 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:43:48 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_char(long int nb)
{
	int	my_rank;

	my_rank = 1;
	if (nb < 0)
	{
		my_rank++;
		nb = -nb;
	}
	while (nb > 10)
	{
		nb /= 10;
		my_rank++;
	}
	if (nb == 10 || nb == -10)
		my_rank++;
	return (my_rank);
}

static char	*rev_str(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
	return (str);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static long int	if_neg(long int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			sign;
	int			i;
	long int	m;

	m = (long int)n;
	str = malloc((sizeof(char) * (num_char(m) + 1)));
	if (!str)
		return (NULL);
	if (n == 0)
		return (ft_strcpy(str, "0"));
	sign = 1;
	if (m < 0)
		sign = -1;
	m = if_neg(m);
	i = 0;
	while (m)
	{
		str[i++] = m % 10 + '0';
		m /= 10;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (rev_str(str));
}
