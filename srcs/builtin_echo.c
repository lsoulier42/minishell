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
		* (doubletab_len(*args) + 1 - nb_options));
	if (!new_args)
		return (0);
	new_args[0] = ft_strdup((*args)[0]);
	if (!new_args[0])
		return (free_double_tab_ret_int(new_args));
	while ((*args)[++i])
	{
		new_args[arg_nb] = ft_strdup((*args)[i]);
		if (!new_args[arg_nb])
			return (ft_free_double_tab(new_args) != NULL);
		arg_nb++;
	}
	new_args[arg_nb] = NULL;
	ft_free_double_tab(*args);
	*args = new_args;
	return (1);
}

char 	*exec_echo_join(char **args)
{
	int i;
	int nb_wd;
	char *str;
	int total_len;

	nb_wd = 0;
	i = -1;
	total_len = 0;
	while (args[++i])
		if (ft_strcmp(args[i], "\0") != 0)
		{
			nb_wd++;
			total_len += ft_strlen(args[i]);
		}
	total_len += nb_wd - 1;
	str = (char*)ft_calloc(total_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (args[++i])
		if (ft_strcmp(args[i], "\0") != 0)
		{
			ft_strcat(str, args[i]);
			if (args[i + 1] && ft_strcmp(args[i + 1], "\0") != 0)
				ft_strcat(str, " ");
		}
	return (str);
}

int		exec_echo(t_data *msh_data, t_cmd *cmd)
{
	int		nb_options;
	char	*str;

	nb_options = nb_n_options(cmd->args);
	if (nb_options > 0)
		if (!remove_n_options(&(cmd->args), nb_options))
			return (EXIT_FAILURE);
	str = exec_echo_join(cmd->args + 1);
	if (!str)
		return (EXIT_FAILURE);
	if (nb_options > 0)
		ft_putstr_fd(str, cmd->redirections[OUT]->fd);
	else
		ft_putendl_fd(str, cmd->redirections[OUT]->fd);
	free(str);
	return (EXIT_SUCCESS);
}
