/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:19:52 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 02:19:59 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_key_is_legit(char *key)
{
	int i;

	i = 0;
	if (ft_isdigit(key[0]) || ft_strcmp(key, "=") == 0)
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int exec_export_one_var(t_list *begin_env, char *key, char *value, int has_equal)
{
	int error;
	int key_exist;

	key_exist = env_key_exist(begin_env, key);
	if (export_key_is_legit(key))
	{
		if (key_exist && has_equal)
			error = !change_env_var(begin_env, key, value);
		else if (!key_exist)
			error = !set_env_var(&begin_env, key, value);
		else
			error = 1;
	}
	else
	{
		format_error("export", key, 0, "not an identifier");
		error = 1;
	}
	return (error == 0);
}

char 	*format_export_line(t_var *env_var)
{
	char	*begin_line;
	int 	definite_len;
	int 	begin_line_len;
	char 	*new_line;

	begin_line = "declare -x ";
	begin_line_len = (int)ft_strlen(begin_line);
	definite_len = begin_line_len + ft_strlen(env_var->key)
			+ 1 + ft_strlen(env_var->value) + 2;
	new_line = (char*)ft_calloc(definite_len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, begin_line, begin_line_len + 1);
	ft_strcat(new_line, env_var->key);
	ft_strcat(new_line, "=\"");
	ft_strcat(new_line, env_var->value);
	ft_strcat(new_line, "\"");
	return (new_line);
}

void	exec_export_print(t_list *begin_env)
{
	t_list	*env;
	char	*line;

	env = begin_env;
	ft_lstsort(&env, &cmp_key_var);
	while (env)
	{
		line = format_export_line((t_var*)env->content);
		ft_putendl_fd(line, 1);
		free(line);
		env = env->next;
	}
}

int	exec_export(t_data *msh_data, t_cmd *cmd)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (!(cmd->args[1]))
		exec_export_print(msh_data->begin_env);
	else
	{
		while (cmd->args[++i])
		{
			if (parse_var(cmd->args[i], &key, &value))
			{
				if (!exec_export_one_var(msh_data->begin_env, key, value,
						unparsed_var_has_equal(cmd->args[i])))
				{
					free(key);
					free(value);
					return (-1);
				}
			}
			else
				return (-1);
		}
	}
	return (0);
}
