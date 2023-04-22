/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:46:51 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/22 17:06:55 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing_error(int type)
{
	if (type == 0)
		ft_putstr_fd("Error, malloc failed\n", 2);
	else if (type == 1)
		ft_putstr_fd("Error, invalide variable\n", 2);
	else if (type == 2)
		ft_putstr_fd("Error, invalide pipe\n", 2);
	else if (type == 3)
		ft_putstr_fd("Error, quotes not close\n", 2);
	else if (type == 4)
		ft_putstr_fd("Error, invalide infile\n", 2);
	else if (type == 5)
		ft_putstr_fd("Error, invalide outfile\n", 2);
	else if (type == 6)
		ft_putstr_fd("Error, invalide format\n", 2);
	else if (type == 7)
		ft_putstr_fd("Error, invalide heredoc\n", 2);
	else if (type == 8)
		ft_putstr_fd("Error, invalide append\n", 2);
	g_return_value = 2;
}