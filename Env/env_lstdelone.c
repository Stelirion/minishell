/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:24:05 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/23 00:52:01 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	if (lst->name)
		free(lst->name);
	if (lst->content)
		free(lst->content);
	free(lst);
}
