/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:14:11 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/22 18:51:22 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_setting_check(t_param *init)
{
	size_t	pipe;
	size_t	command;
	t_param	*param;

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
		return (1);
	if (command - 1 != pipe)
		return (1);
	return (0);
}

t_param	*type_setting(t_param *param)
{
	int		next;
	int		tilt;
	t_param	*init;

	next = 1;
	init = param;
	while (param)
	{
		if (handle_redirect_pipe(&param, &next, &tilt))
			;
		else if (handle_redirect_in(&param, &tilt))
			;
		else if (handle_redirect_out(&param, &tilt))
			;
		else if (handler_type_command(&param, &next))
			;
		else
			param->type = ARG;
		if (tilt)
			return (param_lstclear(&init), NULL);
		param = param->next;
	}
	if (type_setting_check(init))
		return (parsing_error(6), param_lstclear(&init), NULL);
	return (init);
}
