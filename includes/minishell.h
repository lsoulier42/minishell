/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:48:56 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 14:28:55 by louise           ###   ########.fr       */
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

typedef struct	s_cmd
{
	char		*name;
	int 		exit_status;
	t_list		*params;
}				t_cmd;

typedef struct	s_pipe
{
	t_list		*begin_cmd;
	int 		exit_status;
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

typedef struct	s_instruction
{
	char *value;
	int is_quote;
}				t_instruction;

typedef struct	s_user_input
{
	char		*input;
	t_list		*begin_instructions;
	t_list		*begin_pipes;
	t_list		*begin_redirections;
	int 		exit_status;
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
int				doubletab_len(char **tab);
char			*ft_strndup(char *str, int n);

void			init_data(t_data *msh_data, char *envp[]);

void 			set_var(t_var *new_var, char *key, char *value);
void 			del_var(void *var);
t_var			*parse_var(char *str);
int 			cmp_key_var(t_var *var1, t_var *var2);

t_list			*set_env(char *envp[]);
int				set_env_var(t_list **begin_env, char *unparsed);
t_var			*get_env_var(t_list *begin_env, char *key);
void			print_env(t_list *begin);

int 			execute_builtin(t_data *msh_data, t_cmd *cmd);
int 			search_builtin(t_data *msh_data, t_cmd *cmd);
int 			exec_exit(t_data *msh_data, t_cmd *cmd);
int 			exec_env(t_data *msh_data, t_cmd *cmd);
int				exec_unset(t_data *msh_data, t_cmd *cmd);
int				exec_export(t_data *msh_data, t_cmd *cmd);
int				exec_pwd(t_data *msh_data, t_cmd *cmd);
int				exec_cd(t_data *msh_data, t_cmd *cmd);
int 			exec_echo(t_data *msh_data, t_cmd *cmd);


int 			split_cmds(t_list *pipes);
int 			recreate_cmds(t_list **begin_cmds);
t_list			*create_cmd(t_list *instruct);
int 			is_semicolon(t_instruction *it);
int 			add_param(t_list **begin, char *str);

int 			quote_char(char c);
int				count_quote_len(char *str, char quote_c);
int				add_instruct_quote(t_list **begin, char **str);

int				sub_var(t_data *msh_data, t_list *params);
int 			check_key(t_list *env, char *param);
int				parse_params(t_data *msh_data, t_list *params);
int 			sub_interrogation(t_data *msh_data, t_list *params);
int 			sub_absent_key(t_list *params);

int 			is_pipe(t_instruction *it);
t_pipe			*create_pipe(t_list *begin);
t_list			*split_pipes(t_list *instructions);

t_user_input 	*parse_input(t_data *msh_data, char *buffer);

t_list			*create_instruction_el(char *str, int is_quote);
int				create_instruct_std(t_list **begin, char *buffer, int *i);
t_list			*split_instructions(char *buffer);
void 			del_instruction(void *del_void);
int				instruction_len(char *str);
t_instruction	*create_instruction(char *str, int is_quote);

#endif
