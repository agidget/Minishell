/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:49:52 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 11:49:54 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(int *i, char **stop, char *str)
{
	char	*temp;

	*i = space_len(str, 32, 0) - 1;
	temp = strcopy(str, *i);
	*stop = ft_strjoin(temp, "\n");
	free(temp);
}

void	double_input_redir(t_list **main_struct, char *str)
{
	int		i;
	char	*stop;
	int		tmp;
	int		ret;
	char	buf[512];

	init_vars(&i, &stop, str);
	create_temp_file(main_struct);
	tmp = open((*main_struct)->temp_file, O_RDWR | O_CREAT, 0644);
	if (tmp == -1)
		exit(0);
	ret = 1;
	while (ret)
	{
		write(1, "> ", 2);
		ret = read(0, buf, 511);
		buf[ret] = '\0';
		if (ft_strncmp(stop, buf, ft_strlen(buf)) == 0)
			break ;
		ft_putstr_fd(buf, tmp);
	}
	close(tmp);
	tmp = open((*main_struct)->temp_file, O_RDONLY, 0644);
	(*main_struct)->in = tmp;
	free(stop);
}

void	two_redirect(t_list **main_struct, char *str, int j, char *file)
{
	if ((str - j)[0] == '>')
	{
		if ((*main_struct)->out != 1)
			close((*main_struct)->out);
		(*main_struct)->out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if ((str - j)[0] == '<')
	{
		if ((*main_struct)->in != 0)
			close((*main_struct)->in);
		double_input_redir(main_struct, str);
	}
}

int	exit_from_redirects(char *file)
{
	no_file(file);
	return (258);
}

int	if_redirect(t_list **main_struct, char *str, int *i)
{
	char	*file;
	int		len;
	int		j;
	int		flag;

	j = 1;
	flag = prepare_for_redirection(str, &j);
	str = str + j;
	len = space_len(str, 32, 0);
	file = find_filename(str, len, (str - j)[0], flag);
	if (file[0] == 0 || ft_strchr(file, '<') != -1
		|| ft_strchr(file, '>') != -1)
		return (check_syntax_error(file));
	if (flag == 0)
		one_redirect(main_struct, str, j, file);
	else
		two_redirect(main_struct, str, j, file);
	free(file);
	*i = *i + j + len + 1;
	if (errno != 0)
		return (exit_from_redirects(file));
	return (0);
}
