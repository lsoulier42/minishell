#include "minishell.h"
#include <stdio.h>

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

	i = 1;
	while (instructions)
	{
		begin_pipes = get_instruction_pipes(instructions);
		printf("instruction %d :\n", i++);
		j = 1;
		while (begin_pipes)
		{
			k = -1;
			cmds = get_pipes_cmds(begin_pipes);
			cmd = (t_cmd*)cmds->content;
			printf("pipe %d :\n", j++);
			printf("cmd name : %s\n", cmd->name);
			while(cmd->args[++k])
				printf("argument %d : %s\n", k, cmd->args[k]);
			begin_pipes = begin_pipes->next;
		}
		instructions = instructions->next;
	}
}