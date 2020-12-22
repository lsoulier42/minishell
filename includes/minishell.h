/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:48:56 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 22:40:59 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

typedef struct 		s_list_env
{
	char 				*key;
	char 				*value;
	struct s_list_env	*next;
}					t_list_env;

typedef struct		s_data
{
	t_list_env		*begin_env;
	char 			*param;
	int 			cur_level;
	int 			last_return;
	char 			**cmd_history;
	int 			exit_mshl;
}					t_data;

t_list_env			*set_envlist(char *envp[]);
t_list_env			*set_envlist_var(char *env_var);
t_list_env			*env_new_var(char *key, char *value);
void				env_add_back(t_list_env **begin, t_list_env *new);
void				env_add_front(t_list_env **begin, t_list_env *new);
void 				env_del_var(t_list_env **begin, t_list_env *el);
void				env_clear(t_list_env **begin);
char 				*get_env_value(t_list_env *begin, char *key);
void				print_env(t_list_env *begin);
int					search_cmd(char *cmd);
int					execute_cmd(char *cmd, t_data *mshl_data);
int					exec_exit(char *cmd, t_data *mshl_data);
int					exec_env(char *cmd, t_data *mshl_data);
int					exec_unset(char *cmd, t_data *mshl_data);
int					exec_export(char *cmd, t_data *mshl_data);
int					exec_pwd(char *cmd, t_data *mshl_data);
int					exec_cd(char *cmd, t_data *mshl_data);
int 				exec_echo(char *cmd, t_data *mshl_data);
char				*get_param(char *cmd, char *bultin_name);
#endif
