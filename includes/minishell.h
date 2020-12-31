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

typedef enum 	e_error_builtins
{
	EXPORT_INVALID_IDENTIFIER
}				t_error_builtins;

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
	char 	*filename;
	int 	fd;
	int 	export;
	int 	append;
}				t_redirection;

typedef struct	s_cmd
{
	char			*name;
	char 			**args;
	t_redirection	*redirection;
}				t_cmd;

typedef struct	s_pipe
{
	t_list		*begin_cmds;
}				t_pipe;

typedef struct	s_instruction
{
	t_list		*begin_pipes;
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
}				t_user_input;

typedef struct	s_error
{
	char	*str_error;
	char 	*process;
	char 	*arg;
	int		code;
}				t_error;

typedef struct	s_data
{
	t_user_input	*parsed_input;
	int				level;
	int 			last_return;
	t_list			*begin_errors;
	t_list 			*begin_history;
	int 			exit_msh;
}				t_data;

extern t_list	*g_env_list_begin;

void 			format_prompt(void);
void			print_color(char *str, char color);
void 			*free_double_tab(char **tab);
int				doubletab_len(char **tab);
char			*ft_strndup(char *str, int n);
int				free_return_int(void *ptr);
void			*free_return_null(void *ptr);
int 			free_cmd_tabs(char *name, char **args);

void 			init_data(t_data *msh_data);

void 			del_var(void *var);
t_var			*parse_var(char *unparsed);
char 			*parse_var_key(char *unparsed);
char 			*parse_var_value(char *unparsed);
int				cmp_key_var(void *var1_void, void *var2_void);
int				change_env_var_value(char *key, char *new_value);

t_list			*set_env(char *envp[]);
int				set_env_var(t_list **begin_env, char *unparsed);
t_var			*get_env_var(char *key);
void			print_env(void);
char 			*serialize_one_env_var(t_list *env_el);
char			**serialize_env(void);

int 			execute_builtin(t_data *msh_data, t_cmd *cmd);
int 			search_builtin(t_cmd *cmd);
int 			exec_exit(t_data *msh_data, t_cmd *cmd);
int 			exec_env(t_data *msh_data, t_cmd *cmd);
int				exec_unset(t_data *msh_data, t_cmd *cmd);
int				exec_export(t_data *msh_data, t_cmd *cmd);
int 			export_arg_is_legit(char *str);
int 			export_key_already_exist(char *key);
int				exec_pwd(t_data *msh_data, t_cmd *cmd);
int				exec_cd(t_data *msh_data, t_cmd *cmd);
int 			exec_echo(t_data *msh_data, t_cmd *cmd);

t_user_input	*parse_input(char *buffer);
void 			*error_tokens(t_user_input *new);
void 			*error_instructions(t_user_input *new, t_list **tokens);
void 			*error_pipes(t_user_input *new, t_list **tokens);
void 			*error_cmds(t_user_input *new, t_list **tokens);
void			del_user_input(t_user_input *input);

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
int 			token_is_pipe(t_list *el);
int 			token_is_semicolon(t_list *el);
void			*free_token_struct(t_list **begin, char *tmp);

int				ft_isquote(char c);
char 			*sub_quote(char *str);

void			del_instruction(void *instruction_void);
t_instruction	*new_instruction(t_list *begin_pipes);
t_list			*new_instruction_el(t_list *begin_pipes);
t_list			*parse_instructions(t_list *tokens);
int 			add_instruction(t_list **begin_instructions, t_list *begin_pipes);
t_list			*get_instruction_pipes(t_list *instruction_el);
void 			*del_instruction_list(t_list **begin_instructions);

t_pipe			*new_pipe(t_list *begin_cmds);
t_list			*new_pipe_el(t_list *begin_cmds);
void			del_pipe(void *pipe_void);
int 			add_pipe(t_list **begin_pipes, t_list *begin_cmds);
int				parse_pipes(t_list *instructions);
t_list			*get_pipes_cmds(t_list *pipes_el);
int 			del_pipe_list(t_list **begin_pipes);

int				error_operator_is_last_token(void);
int				check_token_list(t_list *tokens);
int 			error_quote_is_not_closed(void);
int 			error_operator_defined(void);
int 			error_lexer(char c);

t_cmd			*new_cmd(char *name, char **args, t_redirection *redirection);
t_list			*new_cmd_el(char *name, char **args, t_redirection *redirection);
void			del_cmd(void *cmd_void);
int 			parse_cmds(t_list *instructions);
int 			create_args_tab(char ***args, t_list *tokens);
int 			parse_one_pipe_cmds(t_list **tokens, t_redirection *redirection);
t_cmd			*get_cmd(t_list *pipe_el);

void			del_redirection(void *redirection_void);
t_redirection	*new_redirection(char *filename, int export, int append);
int 			token_is_redirection(t_list *token_el);
t_redirection	*parse_redirections(t_list *tokens);
int 			create_empty_file_redirection(char *filename, int append);
int 			redirection_is_not_last(t_list *token_el);
int 			parse_one_redirection(t_list *tokens, t_redirection **redirection);
void 			delete_redirection_tokens(t_list **tokens, t_list **previous);

int				expand_vars(t_data msh_data);
char			*get_cmd_next_value(char *str, int *len);
int				expand_one_var(char **cur_arg, int *index);
int				expand_one_arg_vars(t_data msh_data, char **cur_arg);
int				expand_one_cmd_vars(t_data msh_data, t_cmd *cmd);
int				expand_last_return(t_data msh_data, char **cur_arg, int *index);

int 			execute_all_cmds(t_data *msh_data);

t_error			*new_error(char *str_error, char *process, char *arg, int code);

//test functions
void 			print_token_list(t_list *begin);
void 			print_instructions_list(t_list *instructions);
#endif
