#include "minishell.h"

void 	print_double_tab(char **tab)
{
	int i;

	i = -1;
	while(tab[++i])
		printf("|%s|\n", tab[i]);
}

void 		print_token_list(t_list *begin)
{
	t_token *token;

	while (begin)
	{
		token = (t_token*)begin->content;
		printf("{value=|%s| - is_operator=%d\n", token->value, token->is_operator);
		begin = begin->next;
	}
}

void 			print_instructions_list(t_list *instructions)
{
	t_list	*begin_pipes;
	t_list 	*cmds;
	t_cmd	*cmd;
	int 	i;
	int 	j;
	int 	k;
	int 	l;

	i = 1;
	while (instructions)
	{
		begin_pipes = get_instruction_pipes(instructions);
		printf("instruction %d :\n", i++);
		j = 1;
		while (begin_pipes)
		{
			k = -1;
			l = -1;
			cmds = get_pipes_cmds(begin_pipes);
			cmd = (t_cmd*)cmds->content;
			printf("pipe %d :\n", j++);
			printf("nb arguments : %d\n", cmd->argc);
			printf("cmd name : |%s|\n", cmd->args[0]);
			while(cmd->args[++k])
				printf("argument %d : |%s|\n", k, cmd->args[k]);
			while (++l < 2)
				printf("redirection %s: filename: |%s|, fd: %d, type: %s\n",
		   				l == IN ? "in" : "out",
					   cmd->redirections[l]->filename,
					   cmd->redirections[l]->fd,
					   cmd->redirections[l]->type == APPEND ? "append" : "truncate");
			begin_pipes = begin_pipes->next;
		}
		instructions = instructions->next;
	}
}