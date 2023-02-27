/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:55:33 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 14:47:33 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_lstnew(char **content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		error_handler(0);
	if (content)
	{
		if (content[0])
			new->name = content[0];
		else
			new->name = NULL;
		if (content[1])
			new->content = content[1];
		else
			new->content = NULL;
	}
	else
	{
		new->content = NULL;
		new->name = NULL;
	}
	new->next = NULL;
	return (new);
}
