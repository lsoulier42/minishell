/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:20:13 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 02:20:21 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_legit_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int		nb_n_options(char **args)
{
	int	i;
	int	nb;

	i = 1;
	nb = 0;
	while (args[i] && is_legit_n_option(args[i]))
	{
		i++;
		nb++;
	}
	return (nb);
}

int		remove_n_options(char ***args, int nb_options)
{
	char	**new_args;
	int		i;
	int		arg_nb;

	i = nb_options;
	arg_nb = 1;
	new_args = (char**)malloc(sizeof(char*)
		* (ft_double_tab_len(*args) + 1 - nb_options));
	if (!new_args)
		return (0);
	new_args[0] = ft_strdup((*args)[0]);
	if (!new_args[0])
		return (free_double_tab_ret_int(new_args));
	while ((*args)[++i])
	{
		new_args[arg_nb] = ft_strdup((*args)[i]);
		if (!new_args[arg_nb])
			return (ft_double_tab_free(new_args) != NULL);
		arg_nb++;
	}
	new_args[arg_nb] = NULL;
	ft_double_tab_free(*args);
	*args = new_args;
	return (1);
}

int		exec_echo(t_data *msh_data, t_cmd *cmd)
{
	int		nb_options;
	char	*str;

	nb_options = nb_n_options(cmd->args);
	if (nb_options > 0)
		if (!remove_n_options(&(cmd->args), nb_options))
			return (EXIT_FAILURE);
	str = ft_joinstrs(ft_double_tab_len(cmd->args + 1), cmd->args + 1, " ");
	if (!str)
		return (EXIT_FAILURE);
	if (nb_options > 0)
		ft_putstr_fd(str, cmd->redirections[OUT]->fd);
	else
		ft_putendl_fd(str, cmd->redirections[OUT]->fd);
	free(str);
	msh_data->exit_msh = msh_data->exit_msh;
	return (EXIT_SUCCESS);
}
