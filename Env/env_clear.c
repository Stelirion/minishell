/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:20:53 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/23 02:49:48 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_clear(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	free(env);
	env = tmp;
	tmp = env->next;
	free(env);
	env = tmp;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp && tmp->content)
			free(tmp->content);
		if (tmp && tmp->name)
			free(tmp->name);
		if (tmp)
			free(tmp);
	}
}
