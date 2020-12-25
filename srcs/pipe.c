/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:05:05 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 19:51:24 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

t_list	*set_pipes(char *input)
{
	t_list	*begin;
	char 	**pipes;
	int 	i;

	begin = NULL;
	i = -1;
	pipes = ft_split(input, '|');

}

t_list	*set_cmds(char *input)
{
	t_list	*begin;
	char 	**cmds;
	int 	i;

	begin = NULL;
	i = -1;
	cmds = ft_split(input, ';');
	if (cmds)
	{
		while (cmds[++i])
		{
			if (!parse_cmd(&begin, cmds[i]))
				return (NULL);
		}
	}
	return (begin);
}


