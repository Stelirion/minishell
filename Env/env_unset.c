/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:40:06 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/30 14:01:59 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*unset_error(t_env *env, char *str)
{
	ft_putstr_fd("unset : invalid parameter, '", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("' doesn't exist\n", 1);
	return (env);
}

t_env	*env_lstdelone2(t_env *lst)
{
	t_env	*rtn;

	rtn = lst->next;
	if (!lst)
		return (NULL);
	if (lst->name)
		lst->name[0] = '\0';
	if (lst->content)
		lst->content[0] = '\0';
	lst->is_env = 0;
	lst->is_export = 0;
	return (rtn);
}

t_env	*env_unset(t_env *env, char *src)
{
	t_env	*tmp;
	t_env	*next;
	t_env	*last;
	char	*str;

	str = ft_strjoin(src, "=");
	if (!str || !env_search(env, str) || !ft_strcmp(src, "?"))
		return (free(str), unset_error(env, src));
	last = env_search_before(env, str);
	if (last == env)
		return (free(str), env_lstdelone2(last));
	else if (last == env_lstlast(env))
		return (free(str), env);
	else if (last->next == env_lstlast(env))
		return (free(str), env_lstdelone2(last->next), env);
	tmp = last->next;
	last->next = NULL;
	if (!tmp)
		return (env);
	if (tmp->next)
		next = tmp->next;
	else
		next = NULL;
	env_lstdelone2(tmp);
	return (free(str), last->next = next, g_return_value = 0, env);
}
