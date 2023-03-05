/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:55:33 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/05 15:08:04 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_param	*param_lstnew(char *content)
{
	t_param	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		error_handler(130);
	if (content)
	{
		new->content = content;
	}
	else
	{
		new->content = NULL;
	}
	new->next = NULL;
	return (new);
}
