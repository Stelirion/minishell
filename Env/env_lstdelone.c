/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:24:05 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 14:55:20 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	if (lst->name)
	{
		free(lst->name);
		lst->name = NULL;
	}
	if (lst->content)
	{
		free(lst->content);
		lst->content = NULL;
	}
	free(lst);
	lst = NULL;
}
