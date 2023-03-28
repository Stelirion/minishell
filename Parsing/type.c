/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:14:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/28 14:08:53 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	type_setting(t_param *param)
{
	int		next;

	next = 0;
	param->type = CMD;
	param = param->next;
	while (param)
	{
		if (next == 1)
		{
			param->type = CMD;
			next = 0;
		}
		else if (param->content[0] == '|')
		{
			param->type = PIPE;
			next = 1;
		}
		else if (param->content[0] == '<')
		{
			param->type = 9;
			param = param->next;
			param->type = INFILE;
			next = 1;
		}
		else if (param->content[0] == '>')
		{
			param->type = 9;
			param = param->next;
			param->type = OUTFILE;
			next = 1;
		}
		else
			param->type = ARG;
		param = param->next;
		
	}
}