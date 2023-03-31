/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nice_thing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:15:46 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/30 13:06:15 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Tools/Libft/libft.h"

char	*last_str(t_env *env)
{
	char	**tmp;
	char	*str;
	size_t	i;

	i = 0;
	if (env_search(env, "PWD=")->content)
		tmp = ft_split(env_search(env, "PWD=")->content, '/');
	if (!tmp || tmp[0][0] == '\0')
		return ("");
	while (tmp[i])
		i++;
	str = ft_strdup(tmp[i - 1]);
	free_tab(tmp);
	return (str);
}
