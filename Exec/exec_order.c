/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:07:16 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/01 17:25:47 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_swap_m(t_param *first, t_param *second);

void	exec_order(t_param	*param)
{
	t_param	*first;
	t_param	*target;

	if (param->type == CMD)
		return ;
	first = param;
	if (first->type == 9)
		ft_swap_m(first, first->next);
	if (first->type == 9)
		ft_swap_m(first, first->next->next);
	target = first->next;
	while (first->type && first->type != CMD && target)
	{
		target = target->next;
		ft_swap_m(first, target);
	}
}

static void	ft_swap_m(t_param *first, t_param *second)
{
	char	*str;
	int		i;

	if (!first || !second)
		return ;
	str = ft_strdup(first->content);
	free(first->content);
	first->content = second->content;
	second->content = str;
	i = first->type;
	first->type = second->type;
	second->type = i;
}
