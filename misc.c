/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:15:46 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 17:57:12 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	header(void)
{
	ft_putstr_fd ("\x1B[32;1m  ____    ____   _             _  ", 2);
	ft_putstr_fd ("         __             __   __   \n", 2);
	ft_putstr_fd (" |_   \\  /   _| (_)           (_)", 2);
	ft_putstr_fd ("         [  |           [  | [  |  \n", 2);
	ft_putstr_fd ("   |   \\/   |   __   _ .--.   __ ", 2);
	ft_putstr_fd ("   .--.   | |--.  .---.  | |  | |  \n", 2);
	ft_putstr_fd ("   | |\\  /| |  [  | [ `.-. | [  |", 2);
	ft_putstr_fd ("  ( (`\\]  | .-. |/ /__\\  | |  | |  \n", 2);
	ft_putstr_fd ("  _| |_\\/_| |_  | |  | | | |  | |", 2);
	ft_putstr_fd ("   `'.'.  | | | || \\__., | |  | |  \n", 2);
	ft_putstr_fd (" |_____||_____|[___][___||__][___]", 2);
	ft_putstr_fd (" [\\__) )[___]|__]'.__.'[___][___] \n", 2);
	ft_putstr_fd ("\x1B[0m \n", 1);
}

char	*last_str(t_env *env)
{
	char	**tmp;
	char	*str;
	size_t	i;

	i = 0;
	if (env_search(env, "PWD=") && env_search(env, "PWD=")->content)
	{
		if (env_search(env, "PWD=")->content[0] == '\0')
			return ("/");
		tmp = ft_split(env_search(env, "PWD=")->content, '/');
	}
	else
		tmp = ft_split("/", ' ');
	if (tmp && tmp[0] && tmp[0][0] == '\0')
		return (free_tab(tmp), "/");
	while (tmp[i])
		i++;
	if (i > 0)
		str = ft_strdup(tmp[i - 1]);
	else
		str = ft_strdup("/");
	return (free_tab(tmp), str);
}
