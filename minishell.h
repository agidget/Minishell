/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 11:54:15 by agidget           #+#    #+#             */
/*   Updated: 2021/09/01 12:03:24 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <inttypes.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>

# define MSH "\033[38;5;069m[minishell]\033[0m"

int	g_status;

typedef struct s_flags {
	int	pipes;
	int	quote1;
	int	quote2;
	int	flag;
}	t_flags;

typedef struct s_arg {
	char			*val;
	struct s_arg	*next;
	struct s_arg	*head;
}	t_arg;

typedef struct s_list {
	char			*cmd;
	char			**cmd_arr;
	int				in;
	int				out;
	char			*temp_file;
	t_arg			*args;
	struct s_list	*next;
	struct s_list	*head;
}	t_list;

typedef struct s_pipes
{
	int	**fd;
	int	*pid;
}	t_pipes;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_fab_env
{
	t_envp	*orig_env;
	t_envp	*sorted_env;
}	t_fab_env;

char	*ft_strjoin_mod(char const *s1, char const *s2, char c);
char	*cut_str(char *str, int i, int j);
void	create_strings_for_quotes(char **temp, char **temp2, char **new_string);
void	add_char(char **new_string, char c);
void	after_quotes(char **temp_str, char *new_string);
void	ft_error(char *str);
void	with_pipes_builtin(t_pipes *pip, t_list *lst, t_fab_env *envv, int i);
void	with_pipes_execve(t_pipes *pip, t_list *lst, t_fab_env *envv, int i);
void	create_first_arg(t_list **main_struct, char *str, int j);
void	create_arg(t_list **main_struct, char *str, int j);
void	if_echo(t_list **main_struct, char *str, int *j);
void	create_pipe(t_list **main_struct, int *i);
void	no_file(char *filename);
void	command_not_found(char *cmd);
int		print_syntax_error(void);
void	print_fork_error(void);
int		check_syntax_error(char *str);
int		prepare_for_redirection(char *str, int *j);
void	one_redirect(t_list **main_struct, char *str, int j, char *file);
void	two_redirect(t_list **main_struct, char *str, int j, char *file);
char	*find_filename(char *str, int len, char redirect, int flag);
int		exit_from_redirects(char *file);
int		if_redirect(t_list **main_struct, char *str, int *i);
int		check_args(t_list *main_struct);
int		check_str(char *str);
int		if_space_in_quotes(char *str, int *i, char **temp_str);
void	in_struct(t_list **main_struct, char *str, int *i, int flag);
int		parser(t_list **main_struct, char *str, t_fab_env *envv);
int		preparser(char *str);
int		preparser_quotes(char *str);
int		preparser_pipes(char *str);
char	*if_many_questions(int j);
char	*if_question(char *str, int *a);
char	*one_dollar(void);
char	*after_dollar(char *str, t_fab_env	*envv);
char	*several_dollars(char *str, int *a);
char	*dollar(char *str, t_fab_env *envv, int *a);
void	*for_free_int(int **arr, int size);
void	free_pipes(t_pipes *pip, t_list *lst);
void	if_quotes(char **temp_str, char *str, int *i, t_fab_env *envv);
void	double_quote(char **temp_str, char *str, int *i, t_fab_env *envv);
char	*if_quote1(char *str, int *i);
char	*cut_str(char *str, int i, int j);
void	print_error(char *str, char *error);
void	if_space(char *str, char **temp_str, int *i);
void	free_join(char **temp_str, char *new_string);
int		space_len(char *str, char c, int flag);
char	*strcopy(char *source, int i);
void	free_all(t_list *main_struct);
void	signals(void);
void	sig_in_fork(void);
void	create_temp_file(t_list **main_struct);
char	**create_args_array(t_list	*main_struct);
char	*main_parser(char *str, t_fab_env *envv);
void	if_chars(char **temp_str, char *str, int *i, t_fab_env *envv);
int		create_struct(t_list **main_struct, char *str);
t_list	*init_main_struct(void);
int		ft_lstsize(t_list *lst);
void	change_shell_lvl(t_fab_env **env);
void	change_lvl(t_envp	*env);
char	**for_path(t_fab_env *envv);
char	**lst_to_ar(t_fab_env *envv);
int		size_of_envp(t_envp	*env);
void	define_path(t_list *list, t_fab_env *envv);
int		which_cmd(char *cmd);
int		**for_fds(int **fd, int size);
t_pipes	*init_pipes(t_list *lst);
void	no_pipes(t_pipes *pip, t_list *lst, t_fab_env *envv);
void	main_pipes(t_pipes *pip, t_list *lst, t_fab_env *envv);
void	built_in_commands(t_list *main_struct, t_fab_env *envv);
void	if_spaces(t_list **main_struct, char **temp_str, char *str, int *i);
void	if_pipe(t_list **main_struct, char *str, int *i);
int		commands(t_list *main_struct, t_fab_env	*envv);
int		size_of_lst(t_arg *args);
t_envp	*ft_lstnew(char *key, char *value);
void	ft_lstadd_back(t_envp **lst, t_envp *new);
char	*ft_strchr_mod(char *s, int c);
char	*oppos_strchr(char *s, int c);
void	*for_free(char **new);
t_envp	*kv_env(char **envp);
char	*envp_value(char *key, t_fab_env *envv);
void	malloc_error(void *ptr);
char	*one_arg(t_arg *list);
void	my_echo(t_arg *args, int out);
void	my_echo_n(t_arg *args, int out);
char	*get_pwd(void);
void	my_pwd(int out);
void	for_change_oldpwd(char *cur_dir, t_envp *en);
void	change_oldpwd(char *cur_dir, t_fab_env **envv);
void	for_change_pwd(char *cur_dir, t_envp *en);
void	change_pwd(char *cur_dir, t_fab_env **envv);
char	*get_oldpwd(t_fab_env *envv);
void	for_cd_oldpwd_en_part(char *my_oldpwd, t_envp *my_env);
void	for_cd_oldpwd_en(char *my_pwd, char *my_oldpwd, t_envp *my_env, int f);
void	cd_oldpwd_env(char *my_pwd, char *my_oldpwd, t_fab_env **envv);
void	cd_oldpwd(int out, t_fab_env **envv);
void	my_cd_error(char *str);
void	cd_home_error(void);
void	part_my_cd(t_fab_env **envv, char *cur_dir1);
void	my_cd(t_arg *args, int out, t_fab_env **envv);
void	my_envp(int out, t_fab_env *envv);
void	init_fab_env(t_fab_env **envv, char **envp);
int		ft_isalpha_mod(int c);
int		ft_strcmp(char *s1, char *s2);
char	*oppos_strchr_mod(char *s, int c);
void	one_list_kv(t_envp *en, char *arg_key, char *arg_value);
void	for_change_kv(t_fab_env **envv, t_arg **args);
void	my_export(t_fab_env **envv, t_arg **args, int out);
int		part_ex_check(char *val, int i, int flag);
void	export_args_error(char *val);
void	del_el_env(t_envp *en_prev);
void	del_first_env(t_envp *en);
void	unset_args_error(char *val);
int		unset_check_args(char *val);
void	my_unset_one_list(t_envp *en, t_arg *args);
void	my_unset(t_fab_env **envv, t_arg *args);
void	exit_many_arg_error(void);
void	exit_not_num_error(char *val);
int		ft_atoi_mod(char *str);
void	my_exit(t_arg *args, t_list *list);
void	del_fab_en(t_envp *en);
int		check_spaces(char *str, int i);
char	*ft_strjoin_orig(char *s1, char *s2);

#endif
