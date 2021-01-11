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
# define PROMPT_MAX_SIZE 150
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
# include <limits.h>

/*
 * Enum declaration
 */

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

typedef enum	e_ansi_color
{
	RED = '1',
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN
}				t_ansi_color;

typedef enum	e_redirection_type
{
	IN,
	OUT,
	APPEND,
	TRUNCATE
}				t_redirection_type;

typedef enum	e_export_type
{
	EXPORT_CREATE,
	EXPORT_TRUNCATE,
	EXPORT_APPEND
}				t_export_type;

/*
 * Struct declarations
 */

typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

typedef struct s_export_var
{
	char	*key;
	char	*value;
	int		type;
}				t_export_var;

typedef struct s_redirection
{
	char	*filename;
	int		fd;
	int		type;
}				t_redirection;

typedef struct s_cmd
{
	char			*path;
	int 			argc;
	char			**args;
	int             is_last;
	int 			is_piped;
	t_redirection	**redirections;
}				t_cmd;

typedef struct s_pipe
{
	t_list	*begin_cmds;
}				t_pipe;

typedef struct s_instruction
{
	t_list	*begin_pipes;
}				t_instruction;

typedef struct s_token
{
	char	*value;
	int		is_operator;
}				t_token;

typedef struct s_user_input
{
	char	*input;
	t_list	*begin_instructions;
}				t_user_input;

typedef struct s_data
{
	char 			*name;
	t_list			*begin_env;
	t_user_input	*parsed_input;
	int				last_return;
	int				exit_msh;
	int 			exit_value;
}				t_data;

extern int		g_signal_value;

/*
 * Functions that don't match any other domain
 */

void			format_prompt(t_data *msh_data);
void			print_color(char *str, char color);
int				doubletab_len(char **tab);
int				free_return_int(void *ptr);
void			*free_return_null(void *ptr);
int 			free_double_tab_ret_int(char **tab);

/*
 * Functions for environment var management
 */

void			del_var(void *var);
t_var			*new_var(char *key, char *value);
int				parse_var(char *unparsed, char **key, char **value);
char			*parse_var_key(char *unparsed);
char			*parse_var_value(char *unparsed);
int				cmp_key_var(void *var1_void, void *var2_void);
int				key_is_valid(char *str);

/*
 * Functions for environment list management
 */

t_list			*set_env(char *envp[]);
int				set_env_var(t_list **begin_env, char *key, char *value);
int				change_env_var(t_list *begin_env, char *key, char *new_value);
void 			print_env_fd(t_list *begin_env, int fd);
t_var			*get_env_var(t_list *begin_env, char *key);
char			*serialize_one_env_var(t_list *env_el);
char			**serialize_env(t_list *begin_env);
int				env_key_exist(t_list *begin_env, char *key);
int             change_env_shlvl(t_list *begin_env);

/*
 * Functions for builtins
 */

int				execute_builtin(t_data *msh_data, t_cmd *cmd);
int				search_builtin(char *cmd_name);
int				exec_exit(t_data *msh_data, t_cmd *cmd);
int				exec_env(t_data *msh_data, t_cmd *cmd);
int				exec_unset(t_data *msh_data, t_cmd *cmd);
int				exec_pwd(t_data *msh_data, t_cmd *cmd);
/*
 * Specific functions for export
 */
int				exec_export(t_data *msh_data, t_cmd *cmd);
int				exec_export_one_var(t_data *msh_data,
					char *key, char *value, char *arg);
char 			*format_export_line(t_var *env_var);
int				exec_export_print(t_list *begin_env, t_cmd *cmd);
int				var_has_equal(char *str);
int				var_has_plus(char *str);
char			*get_export_key(char *unparsed);
int 			del_export_var(t_export_var *var);
int 			get_export_value(char *unparsed, int has_equal, char **value);
/*
 * Specific functions for cd
 */
int				exec_cd(t_data *msh_data, t_cmd *cmd);
int 			exec_cd_particular_paths(t_data *msh_data,
					t_cmd *cmd, char *new_dir, char *oldpwd);
int 			exec_cd_change_dir(t_data *msh_data, t_cmd *cmd,
					char *new_dir, char *oldpwd);
int				exec_cd_env_var(t_list *begin_env,
					char *new_pathname, char *oldpwd);
/*
 * Specific functions for echo
 */
int				exec_echo(t_data *msh_data, t_cmd *cmd);
int 			remove_n_options(char ***args, int nb_options);
int 			nb_n_options(char **args);
int 			is_legit_n_option(char *str);

/*
 * Functions for the whole parsing module :
 * User input is a struct that will keep the begin list of instructions
 * which are the pipes sequences who are separated by semi-colon.
 * Error functions are free functions depending of timing of error during parsing
 */

t_user_input	*parse_input(char *buffer);
void			*error_tokens(t_user_input *new);
void			*error_instructions(t_user_input *new, t_list **tokens);
void			*error_pipes(t_user_input *new, t_list **tokens);
void			*error_cmds(t_user_input *new, t_list **tokens);
void			del_user_input(t_user_input *input);

/*
 * Functions for the lexer module :
 * User input is divided in tokens which can be a word,
 * multiples words included in quotes, or an operator.
 */

t_token			*new_token(char *value, int is_operator);
void			del_token(void *token_void);
t_list			*new_token_el(char *value, int is_operator);
int				add_token(t_list **begin, char **input);
int				ft_isseparator(char c);
int				ft_isoperator(char c);
t_list			*lexer(char *buffer);
char			*get_token_value(t_list *el);
int				token_is_operator(t_list *el);
int				token_len(char *input);
int				token_len_operator(char *input);
int				token_is_pipe(t_list *el);
int				token_is_semicolon(t_list *el);
void			*free_token_struct(t_list **begin, char *tmp);

/*
 * Functions for instructions management.
 * Instructions are the pipes sequences who are separated by semi-colon.
 */

void			del_instruction(void *instruction_void);
t_instruction	*new_instruction(t_list *begin_pipes);
t_list			*new_instruction_el(t_list *begin_pipes);
t_list			*parse_instructions(t_list *tokens);
int				add_instruction(t_list **bi, t_list *bp);
t_list			*get_instruction_pipes(t_list *instruction_el);
void			*del_instruction_list(t_list **begin_instructions);

/*
 * Functions for pipe sequences management.
 * Pipes sequences are commands who are separated by a pipe char.
 */

t_pipe			*new_pipe(t_list *begin_cmds);
t_list			*new_pipe_el(t_list *begin_cmds);
void			del_pipe(void *pipe_void);
int				add_pipe(t_list **begin_pipes, t_list *begin_cmds);
int				parse_pipes(t_list *instructions);
t_list			*get_pipes_cmds(t_list *pipes_el);
int				del_pipe_list(t_list **begin_pipes);

/*
 * Functions for errors detection and messages during parsing.
 */

int				error_operator_is_last_token(void);
int				check_token_list(t_list *tokens);
int				error_quote_is_not_closed(void);
int				error_operator_defined(void);
int				error_lexer(char c);

/*
 * Functions for command management.
 * Commands contain a path, arguments which first one is the name of the command,
 * a redirection IN and a redirection OUT
 */

t_cmd			*new_cmd(int argc, char **args,
					t_redirection **redirections);
t_list			*new_cmd_el(int argc, char **args,
					t_redirection **redirections);
void			del_cmd(void *cmd_void);
int				parse_cmds(t_list *instructions);
char 			**create_args_tab(t_list *tokens);
int 			parse_one_pipe_cmds(t_list **tokens,
					t_redirection **redirections);
t_cmd			*get_cmd(t_list *pipe_el);

/*
 * Functions for redirection management.
 * A redirection contain a filename parsed from user input,
 * a type which can be APPEND or TRUNCATE,
 * and a FD which will be opened just before execution,
 * except for the empty one to be created if multiple redirections was specified
 */

void			del_redirection(void *redirection_void);
t_redirection	*new_redirection(char *filename, int fd, int type);
int				token_is_redirection(t_list *token_el);
t_redirection	**parse_redirections(t_list *tokens);
int				create_empty_file_redirection(char *filename, int append);
int				redirection_is_not_last(t_list *token_el);
int				parse_one_redirection(t_list *tokens,
					t_redirection ***redirections);
void			delete_redirection_tokens(t_list **tokens, t_list **previous);
int 			open_redirections(t_redirection ***redirections);
int				close_redirections(t_redirection **redirections);
int 			open_redirection_in(t_redirection **redirection);
int				open_redirection_out(t_redirection **redirection);

/*
 * Functions for expander module.
 * Expander user a buffer and a linked list to stack char to be printed.
 * Expander module expand env vars, and reduce quotes and backslashes.
 * Paradigm of spec char is different depending on quotes use :
 * - spec char are separators, quotes, backslash, hash and dollar sign;
 * - no spec char at all is simple quotes are used
 * - weak quote spec char are backslash, quotes, dollar sign and backtick.
 * Functions were puts in expand_vars, _utils, quotes, and backslash
 * which refer to the previous expander module.
 */

int				expand_vars(t_data *msh_data, t_cmd *cmd);
int				expand_one_arg(t_data *msh_data, char **arg);
int				is_escaped(char *str, int char_index);
int				ft_isquote(char c);
int				is_weakquote_specchar(char c);
int 			is_specchar(char c);
char			expand_set_quote_char(char quote_char, char *arg, int i);
int				expand_is_printable(char *arg, int i, char quote_char);
int				expand_is_expandable_var(char *arg, int i, char quote_char);
int 			expand_is_last_return_var(char *arg, int i, char quote_char);
int 			expand_is_flushable_buffer(char *arg, int i,
					int j, char quote_char);
void			expand_init_var(int *i, int *j,
					char *quote_char, t_list **begin);
int				expand_one_arg_finish(char **arg_ptr, t_list **begin,
					char buffer[BUFFER_SIZE + 1], int *j);
char			*expand_get_var_key(char *unparsed);
int				flush_buffer(t_list **begin, char buffer[BUFFER_SIZE + 1],
					int *nb_read);
int				expand_last_return(t_data *msh_data, t_list **begin, int *i);
int				expand_one_var(t_data *msh_data, t_list **begin,
					char *arg, int *i);
int 			no_quote_arg(char *str);
int				trail_null_args(t_cmd *cmd);

/*
 * Execute functions. One function, if found, will be executed depending
 * if it's a builtin or not.
 * If in pipe sequence, the stdout will be set as stdin of the next command.
 * If a redirection is set :
 * - a IN redirection will open the fd after closing stdin
 * - a OUT redirection will write the result on the FD and stdout will be closed.
 * If builtin is the last command, it cannot be opened as a child process
 * so that environment changes can be taken in account.
 */

int				execute_all_cmds(t_data *msh_data);
int				execute_cmd(t_data *msh_data, t_cmd *cmd, int previous_fd, int is_last);
int             execute_last_builtin(t_data *msh_data,
					t_cmd *cmd, int previous_fd);
int             execute_pipe_cmd(t_data *msh_data,
					t_cmd *cmd, int previous_fd);
int				execute_parent_process(t_data *msh_data,
					t_cmd *cmd, pid_t cpid, int pipefd[2]);
int             execute_child_process(t_data *msh_data,
					t_cmd *cmd, int previous_fd, int pipefd[2]);
int             execute_child_process_execve(t_data *msh_data,
					t_cmd *cmd, int pipefd[2]);
int 			child_file_handler(int redir_in_fd,
					int previous_fd, int pipefd_read);
int				write_process_redirection(int read_fd, int out_fd);

/*
 * Functions for general errors management and messages
 */

void			format_error(char *cmd_name, char *arg, int ev, char *str);
void			invalid_identifier(char *cmd_name, char *arg);
void			command_not_found(char *cmd_name);
void			directory_not_found(char *cmd_name);
void			open_file_error(char *filename);
void			execve_error(char *cmd_name, int errno_value);

/*
 * Functions for searching command in path or current dir,
 * and format argv[0] and path
 */

int 			search_path(t_data *msh_data, t_cmd **cmd);
int				search_in_dir(char *dirname, char *cmd_name);
int 			parse_path_and_name(t_cmd **cmd);
int 			parse_path_and_name_absolute(t_cmd **cmd);
int 			parse_path_and_name_relative(t_cmd **cmd);
int				search_path_relative(t_data *msh_data, t_cmd **cmd);
int				search_path_relative_in_path(t_data *msh_data, t_cmd **cmd);

/*
 * Signal handling functions
 */

void    		ctrlc_handler(int signum);
void			ctrlslash_handler(int signum);
void 			sigint_read_handler(int *read_return);
void 			sigint_exec_handler(int *end_of_command);
void 			sigquit_exec_handler(void);

//test functions to be deleted
void			print_token_list(t_list *begin);
void			print_instructions_list(t_list *instructions);
#endif
