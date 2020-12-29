/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:05:19 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 18:05:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	del_redirection(void *redirection_void)
{
	t_redirection *redirection;

	redirection = (t_redirection*)redirection_void;
	free(redirection->input);
	free(redirection->filename);
}
