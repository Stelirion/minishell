/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:04:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/06 17:25:46 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pure(t_env *env, t_param *param)
{
	int	res_fork;

	res_fork = -2;
	printf("pure\n");
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

