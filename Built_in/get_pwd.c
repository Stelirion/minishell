/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:56:05 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/09 14:29:35 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * 2);
	if (!str)
		error_handler(130, NULL, NULL);
	str[1] = '\0';
	while (!getcwd(str, i))
	{
		free(str);
		i++;
		str = malloc(sizeof(char) * (i + 1));
		if (!str)
			error_handler(130, NULL, NULL);
		str[i] = '\0';
	}
	return (str);
}
