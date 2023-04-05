/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nice_thing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:15:46 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/05 19:41:43 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*last_str(t_env *env)
{
	char	**tmp;
	char	*str;
	size_t	i;

	i = 0;
	if (env_search(env, "PWD=")->content)
	{
		if (env_search(env, "PWD=")->content[0] == '\0')
			return ("/");
		tmp = ft_split(env_search(env, "PWD=")->content, '/');
	}
	else
		tmp = NULL;
	if (tmp == NULL)
		return ("/");
	if (tmp[0][0] == '\0')
		return ("/");
	while (tmp[i])
		i++;
	if (i > 0)
		str = ft_strdup(tmp[i - 1]);
	else
		str = ft_strdup("/");
	free_tab(tmp);
	return (str);
}
