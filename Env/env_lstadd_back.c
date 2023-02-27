/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:14 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 14:41:50 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstadd_back(t_env **lst, t_env *next)
{
	t_env	*last;

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
