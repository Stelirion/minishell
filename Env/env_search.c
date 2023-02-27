/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:51:41 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 20:06:56 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_search(t_env *list, char *str)
{
	t_env	*tmp;
	t_env	*rtn;
	int		i;

	if (!str || !list || !list->name)
		return (NULL);
	tmp = list;
	i = ft_strlen(str);
	while (list)
	{
		if (!ft_strncmp(str, list->name, i) && !list->name[i])
			break ;
		list = list->next;
		if (!list)
			return (0);
	}
	rtn = list;
	list = tmp;
	return (rtn);
}

t_env	*env_search_before(t_env *list, char *str)
{
	t_env	*tmp;
	t_env	*rtn;
	int		i;

	if (!str || !list || !list->name)
		return (NULL);
	tmp = list;
	i = ft_strlen(str);
	if (!ft_strncmp(str, list->name, i) && !list->name[i+ 1])
		return (list);
	while (list->next)
	{
		if (!ft_strncmp(str, list->next->name, i) && !list->next->name[i + 1])
		{
			printf("%s\n", list->name);
			break ;
		}
		list = list->next;
		if (!list)
			return (0);
	}
	rtn = list;
	list = tmp;
	return (rtn);
}
