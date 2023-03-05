/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:13:39 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/05 16:49:16 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdio.h>

void	free_tab(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (&str[i])
			free(str[i]);
		i++;
	}
	free(str);
}
