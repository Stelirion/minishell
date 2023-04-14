/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:30:06 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/13 16:15:14 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_prog(t_env *env, int i)
{
	env_clear(env);
	if (i != 0)
		g_return_value = i;
	rl_clear_history();
	exit (g_return_value);
}

void	end_of_prog_exit(t_env *env, t_param *param, int i)
{
	env_clear(env);
	param_lstclear(&param);
	if (i != 0)
		g_return_value = i;
	rl_clear_history();
	exit (g_return_value);
}

void	end_of_prog_exit_fd(t_env *env, t_param *param, int i, int *fd)
{
	env_clear(env);
	param_lstclear(&param);
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
	if (fd[2])
		close(fd[2]);
	if (fd[3])
		close(fd[3]);
	if (i != 0)
		g_return_value = i;
	rl_clear_history();
	exit (g_return_value);
}
