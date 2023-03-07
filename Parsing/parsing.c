/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/07 21:19:39 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_param	*parsing_core(char *line, t_param *param)
{
	size_t	i;
	size_t	start;
	char	*new_str;
	t_param	*new_lst;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i] && line[i] != '\'')
			{
				param_lstclear(&param);
				return (param);
			}
			new_str = ft_substr(line, start + 1, i - start - 1);
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (!line[i] && line[i] != '"')
			{
				param_lstclear(&param);
				return (param);
			}
			new_str = ft_substr(line, start + 1, i - start - 1);
		}
		else
		{
			while (line[i + 1] && line[i + 1] != ' '
				&& line[i + 1] != '\'' && line[i + 1] != '"')
				i++;
			new_str = ft_substr(line, start, i - start + 1);
		}
		i++;
		new_lst = param_lstnew(new_str);
		param_lstadd_back(&param, new_lst);
	}
	return (param);
}
