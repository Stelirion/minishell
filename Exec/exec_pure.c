/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:04:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/11 12:02:55 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pure(t_env *env, t_param *param, int *fd_org)
{
	int	res_fork;
	int	fd[2];

	res_fork = -2;
	fd[0] = dup(fd_org[0]);
	fd [1] = dup(fd_org[1]);
	ft_redirect(param, fd);
	while (param && param->type != CMD)
		param = param->next;
	if (param && is_built_in(param, env) != 1)
		;
	else
		res_fork = try_exec (env, param);
	if (res_fork == -2)
		;
	else if (res_fork != -1)
		waitpid(res_fork, 0, 0);
}


