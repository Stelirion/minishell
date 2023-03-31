/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:14:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/31 17:02:14 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_param	*type_setting(t_param *param)
{
	int		next;
	t_param *init;

	next = 0;
	init = param;
	param->type = CMD;
	param = param->next;
	while (param)
	{
		if (param->content[0] == '|')
		{
			param->type = PIPE;
			next = 1;
		}
		else if (param->content[0] == '<')
		{
			param->type = 9;
			if (!param->next)
			{
				param_lstclear(&init);
				return(NULL);
			}
			param = param->next;
			param->type = INFILE;
		}
		else if (param->content[0] == '>')
		{
			param->type = 9;
			if (!param->next)
			{
				param_lstclear(&init);
				return(NULL);
			}
			param = param->next;
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
	return(init);
}
