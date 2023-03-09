/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:30:06 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/07 21:18:34 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_prog(t_env *env, int i)
{
	env_clear(env);
	if (i != 0)
		g_return_value = i;
	exit (g_return_value);
}

void	end_of_prog_exit(t_env *env, t_param *param, int i)
{
	env_clear(env);
	param_lstclear(&param);
	if (i != 0)
		g_return_value = i;
	exit (g_return_value);
}
