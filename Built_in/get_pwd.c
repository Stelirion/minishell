/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:56:05 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 13:52:10 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(t_env *env)
{
	int		i;
	char	*str;

	(void)env;
	i = 0;
	str = malloc(sizeof(char) * 4096);
	if (!str)
		error_handler(130, NULL, NULL);
	if (!getcwd(str, 4096))
		return (free(str), ft_putstr_fd("PWD unreachable", 1), NULL);
	free(str);
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
			return (error_handler(130, NULL, NULL), str);
		str[i] = '\0';
	}
	return (str);
}
