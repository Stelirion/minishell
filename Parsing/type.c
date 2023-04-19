/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:14:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/19 20:23:46 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_param	*type_setting(t_param *param)
{
	int		next;
	t_param	*init;

	next = 0;
	init = param;
	param->type = CMD;
	param = param->next;
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
	return (init);
}
