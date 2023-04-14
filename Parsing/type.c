/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:14:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/13 11:57:19 by mbrement         ###   ########lyon.fr   */
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
			param->type = INFILE;
		}
		else if (param->content[0] == '>')
		{
			///added by M
			if (param->content[1] && param->content[1] == '>')
			{
				param->type = 9;
				if (!param->next)
					return (parsing_error(5), param_lstclear(&init), NULL);
				param = param->next;
				param->type = OUTFILE;
			}
			///end of added by M
			else 
			{
				param->type = 9;
				if (!param->next)
					return (parsing_error(5), param_lstclear(&init), NULL);
				param = param->next;
				param->type = OUTFILE;
			}
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
