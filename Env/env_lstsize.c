/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:58:00 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/24 17:21:18 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_lstsize(t_env *lst)
{
	int		i;
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
