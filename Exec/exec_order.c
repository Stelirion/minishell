/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:07:16 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/27 14:39:09 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_order(t_param	*param)
{
	t_param	*tmp;
	t_param	*target;
	char	*str;

	if (param->type == CMD)
		return ;
	tmp = param;
	while (tmp->type == 9)
		tmp = tmp->next;
	target = tmp;
	while (target && target->type != CMD)
		target = target->next;
	if (!target)
		return ;
	str = ft_strdup(target->content);
	free(target->content);
	target->content = tmp->content;
	tmp->content = str;
	target->type = tmp->type;
	tmp->type = CMD;
}
