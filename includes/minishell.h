/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:48:56 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 20:24:57 by louise           ###   ########.fr       */
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

typedef enum	e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	TOTAL_BUILTINS
}				t_builtins;

typedef enum 	e_ansi_color
{
	RED = '1',
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN
}				t_ansi_color;

typedef struct 	s_var
{
	char *key;
	char *value;
}				t_var;

typedef struct	s_return
{
	char	*ouput;
	int		exit_status;
}				t_return;

typedef struct	s_cmd
{
	char		*name;
	char		**options;
	char		**params;
	t_return	*out;
}				t_cmd;

typedef struct	s_pipe
{
	t_list		*begin_cmd;
	t_return	*out;
}				t_pipe;

typedef struct	s_redirection
{
	char	*input;
	char 	*output;
	char 	*filename;
	int 	fd;
	int 	direction;
	int 	append;
}				t_redirection;

typedef struct	s_user_input
{
	char		*input;
	t_list		*begin_pipes;
	t_list		*begin_redirections;
	t_list		*begin_quotes;
	t_return	*out;
}				t_user_input;

typedef struct	s_data
{
	t_list			*begin_env;
	t_user_input	*parsed_input;
	int				level;
	int 			last_return;
	t_list 			*begin_history;
	int 			exit_msh;
}				t_data;

void 			format_prompt(t_list *track_env);
void			print_color(char *str, char color);
void 			*free_double_tab(char **tab);

void			init_data(t_data *msh_data, char *envp[]);

void 			set_var(t_var *new_var, char *key, char *value);
void 			del_var(void *var);
t_var			*parse_var(char *str);
int 			cmp_key_var(t_var *var1, t_var *var2);

t_list			*set_env(char *envp[]);
int				set_env_var(t_list **begin_env, char *unparsed);
t_var			*get_env_var(t_list *begin_env, char *key);
void			print_env(t_list *begin);

int				search_cmd(char *cmd, t_data *msh_data);
int				execute_cmd(char *cmd, t_data *msh_data);
int				exec_exit(char *cmd, t_data *msh_data);
int				exec_env(char *cmd, t_data *msh_data);
int				exec_unset(char *cmd, t_data *msh_data);
int				exec_export(char *cmd, t_data *msh_data);
int				exec_pwd(char *cmd, t_data *msh_data);
int				exec_cd(char *cmd, t_data *msh_data);
char			*get_param(char *cmd, char *bultin_name);

int 			exec_echo(char *cmd, t_data *msh_data);
char			*process_echo(char *param, t_data *msh_data);
int 			count_echo(char *param, t_data *msh_data);
void 			count_echo_var(char **param, t_data *msh_data, int *total_len);
void 			process_echo_var(char **param, t_data *msh_data, char **new_str, int *i);

void 			set_cmd(t_cmd *cmd, char *name, char **options, char **params);
char			**get_cmd_options(char **words);
char 			**get_cmd_params(char **words);
int 			parse_cmd(t_list **begin_cmds, char *unparsed);
void			set_return(t_return *ret, char *output, int exit_status);
t_return		*new_return(char *output, int exit_status);

int 			is_quote(char c);
int 			quote_len(char *input, int start);
int				create_quote(char *input, int start, int len, t_list **begin);
t_list			*parse_quotes(char **input);
char			*expand_quote(t_list *begin, int index);

int				sub_var(t_list *env, char ***params_ptr);
int 			sub_var_in_quotes(t_list *env, char **quote_str);
int				sub_quotes(t_list **quotes_begin, char ***params_ptr);
int 			check_key(t_list *env, char *param);

#endif
