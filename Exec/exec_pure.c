/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:04:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/14 10:54:14 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pure(t_env *env, t_param *param, int *fd_org)
{
	int	res_fork;
	int	fd[2];
	int	give[4];

	res_fork = -2;
	fd[0] = dup(fd_org[0]);
	fd[1] = dup(fd_org[1]);
	give[0] = fd_org[1];
	give[1] = fd_org[0];
	give[2] = fd[1];
	give[3] = fd[0];
	ft_redirect(param, fd);
	while (param && param->type != CMD)
		param = param->next;
	if (param && is_built_in(param, env, give) != 1)
		;
	else
	{
		res_fork = try_exec (env, param);
		close(fd[1]);
		if (res_fork == 0)
			end_of_prog_exit_fd(env, param, 0, give);
	}
	if (res_fork == -2)
		;
	else if (res_fork != -1)
		waitpid(res_fork, 0, 0);
	ft_undup(fd);
	close (fd[0]);
	close(fd_org[1]);
}


