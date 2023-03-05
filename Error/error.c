/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:17:07 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/05 15:05:03 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handler(int name)
{
	if (name == 130)
		ft_putstr_fd("Error : a malloc didn't work", 2);
	end_of_prog_exit(g_global, name);
}
