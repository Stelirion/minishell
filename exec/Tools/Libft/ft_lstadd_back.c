/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:14 by mbrement          #+#    #+#             */
/*   Updated: 2023/01/22 15:30:16 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *next)
{
	t_list	*last;

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
