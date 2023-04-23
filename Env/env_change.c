/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:35:56 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/23 00:38:21 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_change(char *name, char *content, t_env *env)
{
	t_env	*tmp;

	if (!name || !env)
		return ;
	tmp = env_search(env, name);
	if (!tmp)
		return (free (content));
	if (tmp->content)
		free(tmp->content);
	tmp->content = content;
}
