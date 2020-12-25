/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:04:49 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 19:48:48 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void 	set_cmd(t_cmd *cmd, char *name, char **options, char **params)
{
	cmd->name = name;
	cmd->options = options;
	cmd->params = params;
}

char		**get_cmd_options(char **words)
{
	int		i;
	int 	j;
	int 	option_index;
	char	**options;
	int 	nb_options;

	i = -1;
	j = -1;
	option_index = 0;
	nb_options = 0;
	while (words[++i])
		if (words[i][0] == '-')
			nb_options++;
	options = (char**)malloc(sizeof(char*) * (nb_options + 1));
	if (options)
	{
		while (words[++j])
		{
			if (words[j][0] == '-')
				if (!(options[option_index++] = ft_substr(words[j],
														  1, ft_strlen(words[j] - 1))))
					return (free_double_tab(options));
		}
		options[option_index] = NULL;
	}
	return (options);
}

char 		**get_cmd_params(char **words)
{
	int		i;
	int 	j;
	int 	param_index;
	char	**params;
	int 	nb_params;

	i = -1;
	j = -1;
	param_index = 0;
	nb_params = 0;
	while (words[++i])
		if (words[i][0] != '-')
			nb_params++;
	params = (char**)malloc(sizeof(char*) * (nb_params + 1));
	if (params)
	{
		while (words[++j])
		{
			if (words[j][0] != '-')
				if (!(params[param_index++] = ft_strdup(words[j])))
					return (free_double_tab(params));
		}
		params[param_index] = NULL;
	}
	return (params);
}

int 		parse_cmd(t_list **begin_cmds, char *unparsed)
{
	char	**words;
	t_cmd	*cmd;
	t_list	*el;

	words = ft_split_charset(unparsed, " \t\n\r\v\f");
	if (!words)
		return (0);
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->name = words[0];
	cmd->options = NULL;
	cmd->params = NULL;
	if (*(words + 1) != NULL)
	{
		cmd->options = get_cmd_options(words + 1);
		cmd->params = get_cmd_params(words + 1);
	}
	set_return(cmd->out, NULL, 0);
	el = ft_lstnew(cmd);
	if (!el)
		return (0);
	ft_lstadd_back(begin_cmds, el);
	return (1);
}
