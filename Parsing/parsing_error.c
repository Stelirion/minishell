/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:46:51 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/06 18:45:09 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parsing_error(int type)
{
    if (type == 0)
        ft_putstr_fd ("Error, malloc failed\n", 1);
    else if (type == 1)
        ft_putstr_fd ("Error, invalide variable\n", 1);
    else if (type == 2)
        ft_putstr_fd ("Error, invalide pipe\n", 1);
    else if (type == 3)
        ft_putstr_fd ("Error, quotes not close\n", 1);
    else if (type == 4)
        ft_putstr_fd ("Error, invalide infile\n", 1);
    else if (type == 5)
        ft_putstr_fd ("Error, invalide outfile\n", 1);
}