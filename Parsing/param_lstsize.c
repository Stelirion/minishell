/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:33:22 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/28 10:43:52 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	param_lstsize(t_param *lst)
{
	size_t	i;
	t_param	*index;

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

size_t	param_lstsize_nb_arg(t_param *lst)
{
	size_t	i;
	t_param	*index;

	i = 0;
	if (!lst)
		return (0);
	index = lst;
	while (index != NULL)
	{
		if (index->type == ARG)
			i++;
		if (index->next == NULL)
			return (i);
		index = index->next;
	}

	return (0);
}
