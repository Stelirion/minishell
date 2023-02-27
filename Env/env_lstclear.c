/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:36:25 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/24 17:25:27 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstclear(t_env **lst)
{
	t_env	*next;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		env_lstdelone(*lst);
		*lst = next;
	}
}
