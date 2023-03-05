/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:30:06 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/05 14:55:43 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_prog(t_env *env, int i)
{
	env_clear(env);
	if (i != 0)
		g_global.return_value = i;
	exit (g_global.return_value);
}

void	end_of_prog_exit(t_global g_global, int i)
{
	env_clear(g_global.env);
	param_lstclear(&g_global.param);
	if (i != 0)
		g_global.return_value = i;
	exit (g_global.return_value);
}
