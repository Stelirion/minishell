/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:43:45 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/24 17:22:04 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstadd_front(t_env **lst, t_env *next)
{
	if (!lst)
		return ;
	next->next = *lst;
	*lst = next;
}
