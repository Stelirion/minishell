/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:58:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/08 15:16:44 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipe(t_env *env, t_param *param)
{
	int	res_fork[2];

	res_fork[0] = -2;
	res_fork[1] = fork();
	if (res_fork[1] == 0)
	{
		while (param)
		{
			while (param && param->type != CMD)
				param = param->next;
			if (!param)
				break ;
			if (param && is_built_in(param, env) != 1)
				;
			else
				res_fork[0] = try_exec (env, param);
			param = param->next;
		}
		end_of_prog_exit(env, param, 0);
	}
	else if (res_fork[1] == -1)
		ft_putstr_fd("Fork didn't work", 2);
	else
		waitpid(res_fork[1], 0, 0);
}
