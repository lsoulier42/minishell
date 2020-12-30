/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:40:10 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/30 14:40:18 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_next_value(t_list *env, char *str, int *len)
{
	char	*key;
	t_var	*var;
	char 	*value;

	if (ft_isdigit(str[0]))
	{
		*len = 1;
		return (ft_strdup(""));
	}
	else
		while (str[*len] && (ft_isalnum(str[*len]) || str[*len] == '_'))
			*len += 1;
	key = ft_strndup(str, *len);
	if (!key)
		return (NULL);
	var = get_env_var(env, key);
	if (!var)
		value = ft_strdup("");
	else
		value = ft_strdup(var->value);
	free(key);
	return (value);
}

int		expand_one_var(t_list *env, char **cur_arg, int *index)
{
	int 	key_len;
	char	*var_value;
	char 	*new_cur_arg;

	key_len = 0;
	var_value = get_cmd_next_value(env, *cur_arg + *index + 1, &key_len);
	if (!var_value)
		return (0);
	new_cur_arg = (char*)ft_calloc(ft_strlen(*cur_arg)
		- key_len + ft_strlen(var_value), sizeof(char*));
	if (!new_cur_arg)
		return (free_str_return_int(var_value));
	ft_strlcpy(new_cur_arg, *cur_arg, *index + 1);
	ft_strcat(new_cur_arg, var_value);
	ft_strcat(new_cur_arg, *cur_arg + *index + key_len + 1);
	free(*cur_arg);
	*index += ft_strlen(var_value);
	free(var_value);
	*cur_arg = new_cur_arg;
	return (1);
}

int expand_one_arg_vars(t_list *env, char **cur_arg)
{
	int 	i;

	i = 0;
	while ((*cur_arg)[i])
	{
		if ((*cur_arg)[i] == '$' && (*cur_arg)[i + 1] != '\0'
			&& !ft_isspace((*cur_arg)[i + 1]) && (*cur_arg)[i + 1] != '$')
		{
			if (!expand_one_var(env, cur_arg, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int expand_one_cmd_vars(t_list *env, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (!expand_one_arg_vars(env, &(cmd->args[i])))
			return (0);
		i++;
	}
	return (1);
}

int expand_vars(t_list *env, t_user_input *parsed_input)
{
	t_list	*instructions;
	t_list	*pipes;
	t_cmd	*cmd;

	instructions = parsed_input->begin_instructions;
	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			cmd = get_cmd(pipes);
			if (!expand_one_cmd_vars(env, cmd))
				return (0);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}