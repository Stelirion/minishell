/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:18:03 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 14:06:58 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *list)
{
	while (list)
	{
		if (list->is_env == 1)
		{
			ft_putstr_fd(list->name, 1);
			ft_putstr_fd(list->content, 1);
			ft_putchar_fd('\n', 1);
		}
		list = list->next;
	}
}
