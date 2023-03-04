/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:58:00 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/01 02:13:34 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	env_lstsize(t_env *lst)
{
	size_t	i;
	t_env	*index;

	i = 0;
	if (!lst)
		return (0);
	index = lst;
	while (index->next != NULL)
	{
		index = index->next;
		i++;
		if (index->next == NULL)
			return (i + 1);
	}
	return (1);
}
