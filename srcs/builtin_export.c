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

int		exec_export_one_var(t_list *begin_env, t_export_var *var)
{
	char *key;
	char *value;

	key = ft_strdup(var->key);
	if (!key)
		return (0);
	if (var->value)
	if (var->type == EXPORT_CREATE)
	{
		if (!set_env_var(&begin_env, var->key, var->value))

	}

	/*key_exist = env_key_exist(msh_data->begin_env, key);
	has_equal = unparsed_var_has_equal(arg);
	if (key_is_valid(key))
	{
		if (key_exist && has_equal)
			error = !change_env_var(msh_data->begin_env, key, value);
		else if (!key_exist)
			error = !set_env_var(&msh_data->begin_env, key, value);
		else
			error = 1;
	}
	else
	{
		invalid_identifier("export", arg);
		error = 1;
	}*/
	return (error == 0);
}

char	*format_export_line(t_var *env_var)
{
	char	*begin_line;
	int		definite_len;
	int		begin_line_len;
	char	*new_line;

	begin_line = "declare -x ";
	begin_line_len = (int)ft_strlen(begin_line);
	definite_len = begin_line_len + ft_strlen(env_var->key);
	if (env_var->value)
		definite_len += ft_strlen(env_var->value) + 3;
	new_line = (char*)ft_calloc(definite_len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, begin_line, begin_line_len + 1);
	ft_strcat(new_line, env_var->key);
	if (env_var->value)
	{
		ft_strcat(new_line, "=");
		ft_strcat(new_line, "\"");
		ft_strcat(new_line, env_var->value);
		ft_strcat(new_line, "\"");
	}
	return (new_line);
}

int		exec_export_print(t_list *begin_env, t_cmd *cmd)
{
	t_list	*env;
	char	*line;

	env = begin_env;
	ft_lstsort(&env, &cmp_key_var);
	while (env)
	{
		line = format_export_line((t_var*)env->content);
		ft_putendl_fd(line, cmd->redirections[OUT]->fd);
		free(line);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int exec_export_parsing(t_list *begin_env, char *unparsed, t_export_var *var)
{
	int equal_sign;
	int plus_sign;
	t_var *env_var;

	if (!unparsed || (unparsed != NULL && !(*unparsed)))
		return (0);
	equal_sign = var_has_equal(unparsed);
	plus_sign = var_has_plus(unparsed);
	if(equal_sign == -1 || plus_sign == -1)
		return (0);
	var->key = get_export_key(unparsed);
	if (!var->key)
		return (0);
	var->type = EXPORT_CREATE;
	env_var = get_env_var(begin_env, var->key);
	if (env_var != NULL && plus_sign)
		var->type = EXPORT_APPEND;
	else if (env_var)
		var->type = EXPORT_TRUNCATE;
	var->value = NULL;
	if (!get_export_value(unparsed, equal_sign, &var->value))
		return (0);
	return (1);
}

int 	del_export_var(t_export_var *var)
{
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	return (0);
}

int		exec_export(t_data *msh_data, t_cmd *cmd)
{
	int				i;
	t_export_var	var;

	i = 0;
	if (!(cmd->args[1]))
		return (exec_export_print(msh_data->begin_env, cmd));
	while (cmd->args[++i])
	{
		if(!exec_export_parsing(msh_data->begin_env, cmd->args[i], &var))
			return (EXIT_FAILURE);
		if (!exec_export_one_var(msh_data->begin_env, &var))
			return (del_export_var(&var) + EXIT_FAILURE);
		del_export_var(&var);
	}
	return (EXIT_SUCCESS);
}
