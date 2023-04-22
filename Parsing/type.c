/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:14:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/21 22:59:54 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_param	*type_setting(t_param *param)
{
	int		next;
	t_param	*init;
	size_t	pipe;
	size_t	command;

	next = 1;
	init = param;
	while (param)
	{
		if (param->content[0] == '|')
		{
			param->type = PIPE;
			if (!param->next)
				return (parsing_error(2), param_lstclear(&init), NULL);
			next = 1;
		}
		else if (param->content[0] == '<')
		{
			param->type = 9;
			if (!param->next)
				return (parsing_error(4), param_lstclear(&init), NULL);
			param = param->next;
			if (param->content[0] == '<')
			{
				param->type = 9;
				if (!param->next)
					return (parsing_error(7), param_lstclear(&init), NULL);
				param = param->next;
				param->type = HEREDOC;
			}
			else
				param->type = INFILE;
		}
		else if (param->content[0] == '>')
		{
			param->type = 9;
			if (!param->next)
				return (parsing_error(4), param_lstclear(&init), NULL);
			param = param->next;
			if (param->content[0] == '>')
			{
				param->type = 9;
				if (!param->next)
					return (parsing_error(8), param_lstclear(&init), NULL);
				param = param->next;
				param->type = APPEND;
			}
			else
				param->type = OUTFILE;
		}
		else if (next == 1)
		{
			param->type = CMD;
			next = 0;
		}
		else
			param->type = ARG;
		param = param->next;
	}
	param = init;
	command = 0;
	pipe = 0;
	while (param)
	{
		if (param->type == CMD)
			command++;
		else if (param->type == PIPE)
			pipe++;
		param = param->next;
	}
	if (command == 0)
		return (parsing_error(6), param_lstclear(&init), NULL);
	if (command - 1 != pipe)
		return (parsing_error(6), param_lstclear(&init), NULL);
	return (init);
}
