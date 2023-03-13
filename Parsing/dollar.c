/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:18:10 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/13 13:36:57 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar(char *str, t_env *env)
{
	char	*rtn;

	if (ft_strcmp("$?", str))
	{
		ft_putnbr_fd(g_return_value, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_return_value = 127;
		return (ft_strdup(""));
	}
	str++;
	rtn = ft_strdup(env_search(env, str)->content);
	str--;
	return (rtn);
}

