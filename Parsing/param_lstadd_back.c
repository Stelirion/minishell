/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:14 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/01 01:24:16 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	param_lstadd_back(t_param **lst, t_param *next)
{
	t_param	*last;

	if (!next || !lst)
		return ;
	if (!*lst)
	{
		*lst = next;
		return ;
	}
	last = *lst;
	while (last)
	{
		if (last->next == NULL)
		{
			last->next = next;
			return ;
		}
		last = last->next;
	}
}
