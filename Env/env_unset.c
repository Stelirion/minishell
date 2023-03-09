/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:40:06 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/07 21:09:52 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*unset_error(t_env *env, char *str)
{
	ft_putstr_fd("unset : invalid parameter, '", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("' doen't exist\n", 1);
	return (env);
}

t_env	*env_unset(t_env *env, char *src)
{
	t_env	*tmp;
	t_env	*next;
	t_env	*last;
	char	*str;

	str = ft_strjoin(src, 	"=");
	if (!str || !env_search(env, str))
	{
		free(str);
		return (unset_error(env, src));
	}
	last = env_search_before(env, str);
	if (last == env)
	{
		env = env->next;
		env_lstdelone(last);
		return (free(str), env);
	}
	else if (last == env_lstlast(env))
		return (free(str), env);
	else if (last->next == env_lstlast(env))
	{
		env_lstdelone(last->next);
		last->next = NULL;
		return (free(str), env);
	}
	tmp = last->next;
	last->next = NULL;
	if (!tmp)
		return (free(str), env);
	if (tmp->next)
		next = tmp->next;
	env_lstdelone(tmp);
	last->next = next;
	  g_return_value = 0;
	return (free(str), env);
}
