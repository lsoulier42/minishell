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

typedef enum e_builtins
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

typedef enum e_error_builtins
{
	EXPORT_INVALID_IDENTIFIER
}				t_error_builtins;

typedef enum e_ansi_color
{
	RED = '1',
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN
}				t_ansi_color;

typedef enum e_redirection_type
{
	IN,
	OUT,
	APPEND,
	TRUNCATE
}				t_redirection_type;

typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

typedef struct s_redirection
{
	char	*filename;
	int		fd;
	int		type;
}				t_redirection;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int             is_last;
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

void			format_prompt(t_data *msh_data);
void			print_color(char *str, char color);
int				doubletab_len(char **tab);
int				free_return_int(void *ptr);
void			*free_return_null(void *ptr);
int				free_cmd_tabs(char *name, char **args);

void			del_var(void *var);
t_var			*new_var(char *key, char *value);
int				parse_var(char *unparsed, char **key, char **value);
char			*parse_var_key(char *unparsed);
char			*parse_var_value(char *unparsed);
int				cmp_key_var(void *var1_void, void *var2_void);
int				unparsed_var_has_equal(char *str);
int				key_is_valid(char *str);

t_list			*set_env(char *envp[]);
int				set_env_var(t_list **begin_env, char *key, char *value);
int				change_env_var(t_list *begin_env, char *key, char *new_value);
void 			print_env_fd(t_list *begin_env, int fd);
t_var			*get_env_var(t_list *begin_env, char *key);
char			*serialize_one_env_var(t_list *env_el);
char			**serialize_env(t_list *begin_env);
int				env_key_exist(t_list *begin_env, char *key);
int             change_env_shlvl(t_list *begin_env);

int				execute_builtin(t_data *msh_data, t_cmd *cmd);
int				search_builtin(char *cmd_name);
int				exec_exit(t_data *msh_data, t_cmd *cmd);
int				exec_env(t_data *msh_data, t_cmd *cmd);
int				exec_unset(t_data *msh_data, t_cmd *cmd);
int				exec_export(t_data *msh_data, t_cmd *cmd);
int 			exec_export_one_var(t_data *msh_data, char *key, char *value, int has_equal);
char 			*format_export_line(t_var *env_var);
void	        exec_export_print(t_list *begin_env, t_cmd *cmd);
int				exec_pwd(t_data *msh_data, t_cmd *cmd);
int				exec_cd(t_data *msh_data, t_cmd *cmd);
int             exec_cd_particular_paths(t_data *msh_data, char **new_dir);
int				exec_echo(t_data *msh_data, t_cmd *cmd);

t_user_input	*parse_input(char *buffer);
void			*error_tokens(t_user_input *new);
void			*error_instructions(t_user_input *new, t_list **tokens);
void			*error_pipes(t_user_input *new, t_list **tokens);
void			*error_cmds(t_user_input *new, t_list **tokens);
void			del_user_input(t_user_input *input);

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

int				ft_isquote(char c);
char			*sub_quote(char *str);

void			del_instruction(void *instruction_void);
t_instruction	*new_instruction(t_list *begin_pipes);
t_list			*new_instruction_el(t_list *begin_pipes);
t_list			*parse_instructions(t_list *tokens);
int				add_instruction(t_list **bi, t_list *bp);
t_list			*get_instruction_pipes(t_list *instruction_el);
void			*del_instruction_list(t_list **begin_instructions);

t_pipe			*new_pipe(t_list *begin_cmds);
t_list			*new_pipe_el(t_list *begin_cmds);
void			del_pipe(void *pipe_void);
int				add_pipe(t_list **begin_pipes, t_list *begin_cmds);
int				parse_pipes(t_list *instructions);
t_list			*get_pipes_cmds(t_list *pipes_el);
int				del_pipe_list(t_list **begin_pipes);

int				error_operator_is_last_token(void);
int				check_token_list(t_list *tokens);
int				error_quote_is_not_closed(void);
int				error_operator_defined(void);
int				error_lexer(char c);

t_cmd			*new_cmd(char *name, char **args, t_redirection **redirections);
t_list			*new_cmd_el(char *name, char **args, t_redirection **redirections);
void			del_cmd(void *cmd_void);
int				parse_cmds(t_list *instructions);
int				create_args_tab(char ***args, t_list *tokens);
int 			parse_one_pipe_cmds(t_list **tokens, t_redirection **redirections);
t_cmd			*get_cmd(t_list *pipe_el);

void			del_redirection(void *redirection_void);
t_redirection	*new_redirection(char *filename, int fd, int type);
int				token_is_redirection(t_list *token_el);
t_redirection	**parse_redirections(t_list *tokens);
int				create_empty_file_redirection(char *filename, int append);
int				redirection_is_not_last(t_list *token_el);
int				parse_one_redirection(t_list *tokens, t_redirection ***redirections);
void			delete_redirection_tokens(t_list **tokens, t_list **previous);
int 			open_redirections(t_redirection ***redirections);
int				close_redirections(t_redirection **redirections);

int				expand_vars(t_data *msh_data, t_cmd *cmd);
int				expand_one_arg_vars(t_data *msh_data, char **cur_arg);
int				expand_one_var(t_list *begin_env, char **cur_arg, int *index);
char			*expand_get_var_value(t_list *begin_env, char *str, int *len);
int				expand_last_return(t_data *msh_data, char **cur_arg, int *index);

int				execute_all_cmds(t_data *msh_data);
int             execute_cmd(t_data *msh_data, t_list *pipes, int fdstdin);
int             execute_last_builtin(t_data *msh_data, t_cmd *cmd, int previous_fd);
int             execute_pipe_cmd(t_data *msh_data, t_cmd *cmd, int previous_fd);
int             execute_parent_process(t_cmd *cmd, int pipefd[2]);
int             execute_child_process(t_data *msh_data, t_cmd *cmd, int previous_fd, int pipefd[2]);
int             execute_child_process_execve(t_data *msh_data, t_cmd *cmd, int pipefd[2]);

void			format_error(char *cmd_name, char *arg, int ev, char *str);
void			invalid_identifier(char *msh_name, char *cmd_name, char *arg);

char			*search_path(t_list *begin_env, char *cmd_name);
char 			*search_path_absolute(t_list *begin_env, char *cmd_name);
char 			*search_path_relative(t_list *begin_env, char *cmd_name);
char 			*format_found_path(char *found, char *cmd_name);
int 			search_one_relative_path(char *pathname, char *cmd_name);

void    		ctrlc_handler(int signum);
void			ctrlslash_handler(int signum);
void 			sigint_read_handler(int *read_return);
void 			sigint_exec_handler(int *end_of_command);
void 			sigquit_exec_handler(void);

//test functions
void			print_token_list(t_list *begin);
void			print_instructions_list(t_list *instructions);
#endif
