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

int 	is_legit_n_option(char *str)
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

int 	nb_n_options(char **args)
{
	int	i;
	int	nb;

	i = -1;
	nb = 0;
	while (args[++i])
		if (is_legit_n_option(args[i]))
			nb++;
	return (nb);
}

int 	remove_n_options(char ***args, int nb_options)
{
	char	**new_args;
	int		i;
	int		arg_nb;

	i = -1;
	arg_nb = 0;
	new_args = (char**)malloc(sizeof(char*)
			* (doubletab_len(*args) + 1 - nb_options));
	if (!new_args)
		return (0);
	while ((*args)[++i])
	{
		if (!is_legit_n_option((*args)[i]))
		{
			new_args[arg_nb] = ft_strdup((*args)[i]);
			if (!new_args[arg_nb])
				return (free_double_tab(new_args) != NULL);
			arg_nb++;
		}
	}
	new_args[arg_nb] = NULL;
	free_double_tab(*args);
	*args = new_args;
	return (1);
}

int 	exec_echo(t_data *msh_data, t_cmd *cmd)
{
	int		nb_option;
	char	*str;

	nb_option = nb_n_options(cmd->args);
	if (nb_option > 0)
		if (!remove_n_options(&(cmd->args), nb_option))
			return (-1);
	str = ft_joinstrs(doubletab_len(cmd->args + 1), cmd->args + 1, " ");
	if (!str)
		return (-1);
	if (nb_option > 0)
		ft_putstr(str);
	else
		ft_putendl_fd(str, STDOUT_FILENO);
	free(str);
	return (0);
}
