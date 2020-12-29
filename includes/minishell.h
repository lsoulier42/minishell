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

typedef struct	s_redirection
{
	char	*input;
	char 	*filename;
	int 	fd;
	int 	direction;
	int 	append;
}				t_redirection;

typedef struct	s_cmd
{
	char			*name;
	char 			**args;
	t_redirection	*redir;
	int 			exit_status;
}				t_cmd;

typedef struct	s_pipe
{
	t_list		*begin_cmds;
	int 		exit_status;
}				t_pipe;

typedef struct	s_instruction
{
	t_list		*begin_pipes;
	int 		exit_status;
}				t_instruction;

typedef struct	s_token
{
	char	*value;
	int 	is_operator;
}				t_token;

typedef struct	s_user_input
{
	char		*input;
	t_list		*begin_instructions;
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

int				sub_var(t_data *msh_data, t_list *params);
int 			check_key(t_list *env, char *param);
int				parse_params(t_data *msh_data, t_list *params);
int 			sub_interrogation(t_data *msh_data, t_list *params);
int 			sub_absent_key(t_list *params);

t_user_input	*parse_input(char *buffer);
void 			*error_input(t_user_input *new);
void 			*error_tokens(t_user_input *new);
void 			*error_instructions(t_user_input *new, t_list **tokens);
void			del_user_input(void *input_void);

t_token			*new_token(char *value, int is_operator);
void 			del_token(void *token_void);
t_list			*new_token_el(char *value, int is_operator);
int 			add_token(t_list **begin, char **input);
int 			ft_isseparator(char c);
int 			ft_isoperator(char c);
t_list			*split_tokens(char *buffer);
char			*get_token_value(t_list *el);
int 			token_is_operator(t_list *el);
int 			token_len(char *input);
int 			token_len_operator(char *input);
void			del_token_el(t_list *token_el);
int 			token_is_pipe(t_list *el);
int 			token_is_semicolon(t_list *el);

void			del_instruction(void *instruction_void);
t_instruction	*new_instruction(t_list *begin_pipes, int exit_status);
t_list			*new_instruction_el(t_list *begin_pipes, int exit_status);
t_list			*parse_instructions(t_list *tokens);
int 			add_instruction(t_list **begin_instructions, t_list *begin_pipes);
t_list			*get_instruction_pipes(t_list *instruction_el);

t_pipe			*new_pipe(t_list *begin_cmds, int exit_status);
t_list			*new_pipe_el(t_list *begin_cmds, int exit_status);
void			del_pipe(void *pipe_void);
int 			add_pipe(t_list **begin_pipes, t_list *begin_cmds);
int				parse_pipes(t_list *instructions);
t_list			*get_pipes_cmds(t_list *pipes_el);


//test functions
void 			print_token_list(t_list *begin);
void 			print_instructions_list(t_list *instructions);
#endif
