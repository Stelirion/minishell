/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:40:06 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/01 19:41:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_unset(t_env *env, char *str)
{
	t_env	*tmp;
	t_env	*next;
	t_env	*last;

	if (!str)
		return (env);
	last = env_search_before(env, str);
	if (last == env)
	{
		env = env->next;
		env_lstdelone(last);
		return (env);
	}
	if (last == env_lstlast(env))
		return (env);
	tmp = last->next;
	last->next = NULL;
	if (!tmp)
		return (env);
	if (tmp->next)
		next = tmp->next;
	env_lstdelone(tmp);
	last->next = next;
	g_return_value = 0;
	return (env);
}
