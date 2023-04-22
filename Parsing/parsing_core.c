/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:15:19 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/22 17:22:01 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	split_token(char *line, size_t start)
{
	size_t	i;
	int		status;

	i = start;
	status = 0;
	if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		return (i + 1);
	while (line[i])
	{
		status = get_status(line[i], status);
		if (status == 0 && line[i] == ' ')
			return (i);
		if (status == 0 && line[i] == '|')
			return (i);
		if (status == 0 && line[i] == '>')
			return (i);
		if (status == 0 && line[i] == '<')
			return (i);
		i++;
	}
	return (i);
}

t_param	*parsing_core(char *line, t_param *param, t_env	*env)
{
	size_t	i;
	size_t	len;
	size_t	start;
	char	*next_token;
	t_param	*new_lst;

	i = 0;
	len = ft_strlen(line);
	if (!token_format(line))
		return (parsing_error(6), free(param), NULL);
	while (i <= len)
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		i = split_token(line, start);
		next_token = ft_substr(line, start, i - start);
		if (!next_token)
			return (parsing_error(0), free(param), NULL);
		next_token = manage_quote(next_token, env);
		if (!next_token)
			return (param_lstclear(&param), NULL);
		new_lst = param_lstnew(next_token);
		if (!new_lst)
			return (parsing_error(0), param_lstclear(&param), NULL);
		param_lstadd_back(&param, new_lst);
	}
	return (param);
}

