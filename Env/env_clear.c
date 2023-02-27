/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:20:53 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 15:25:05 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_clear(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->next)
			free(tmp->next);
		if (tmp->content)
			free(tmp->content);
		if (tmp->name)
			free(tmp->name);
	}
}