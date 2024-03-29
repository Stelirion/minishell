/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:17:07 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/31 13:21:39 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handler(int name, t_env *env, t_param *param)
{
	if (name == 130)
		ft_putstr_fd("Error : a malloc didn't work", 2);
	else if (name == 131)
		ft_putstr_fd("Error : a Pipe explode", 2);
	end_of_prog_exit(env, param, name);
}
