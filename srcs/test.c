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
	t_list	*begins_pipes;
	t_pipe 	*pipe;
	t_token *token;
	int 	i;
	int 	j;

	i = 1;
	while (instructions)
	{
		begins_pipes = get_instruction_pipes(instructions);
		printf("instruction %d :\n", i++);
		j = 1;
		while (begins_pipes)
		{
			pipe = (t_pipe*)begins_pipes->content;
			printf("pipe %d :\n", j++);
			print_token_list(pipe->begin_cmds);
			begins_pipes = begins_pipes->next;
		}
		instructions = instructions->next;
	}
}