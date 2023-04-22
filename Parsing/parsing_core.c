/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:15:19 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/22 22:08:05 by ngennaro         ###   ########.fr       */
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
	t_parsing_core	var;
	t_param			*new_lst;

	var.i = 0;
	var.len = ft_strlen(line);
	while (var.i <= var.len)
	{
		while (line[var.i] == ' ')
			var.i++;
		if (!line[var.i])
			break ;
		var.start = var.i;
		var.i = split_token(line, var.start);
		var.next_token = ft_substr(line, var.start, var.i - var.start);
		if (!var.next_token)
			return (parsing_error(0), free(param), NULL);
		var.next_token = manage_quote(var.next_token, env);
		if (!var.next_token)
			return (param_lstclear(&param), NULL);
		new_lst = param_lstnew(var.next_token);
		if (!new_lst)
			return (parsing_error(0), param_lstclear(&param), NULL);
		param_lstadd_back(&param, new_lst);
	}
	return (param);
}
