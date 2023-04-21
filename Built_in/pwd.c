/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:32:30 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/21 20:00:04 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	*str;

	str = get_pwd(NULL);
	ft_putstr_fd(str, 1);
	write (1, "\n", 1);
	free(str);
	g_return_value = 0;
}
