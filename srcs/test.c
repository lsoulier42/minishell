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

