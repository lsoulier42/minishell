/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:03:01 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 22:15:10 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_data *msh_data, t_cmd *cmd)
{
	t_var	*pwd;
	char	*current;

	pwd = get_env_var(msh_data->begin_env, "PWD");
	if (!pwd)
		current = getcwd(NULL, 0);
	else
		current = ft_strdup(pwd->value);
	if (!current)
		return (EXIT_FAILURE);
	ft_putendl_fd(current, cmd->redirections[OUT]);
	free(current);
	msh_data->last_return = EXIT_SUCCESS;
	return (msh_data->last_return);
}

int	exec_env(t_data *msh_data, t_cmd *cmd)
{
	print_env_fd(msh_data->begin_env, cmd->redirections[OUT]);
	msh_data->last_return = EXIT_SUCCESS;
	return (msh_data->last_return);
}

int	exec_unset(t_data *msh_data, t_cmd *cmd)
{
	int		i;
	t_var	*to_remove;

	i = 0;
	while (cmd->args[++i])
	{
		if (key_is_valid(cmd->args[i]))
		{
			to_remove = get_env_var(msh_data->begin_env, cmd->args[i]);
			if (to_remove != NULL)
				ft_lstrm_if(&(msh_data->begin_env), to_remove,
					&cmp_key_var, del_var);
		}
		else
		{
			invalid_identifier("unset", cmd->args[i]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
