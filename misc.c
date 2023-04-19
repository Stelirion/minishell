/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:15:46 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/20 01:40:14 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	header(void)
{
	ft_putstr_fd ("\x1B[32;1m  ____    ____   _             _  ", 1);
	ft_putstr_fd ("         __             __   __   \n", 1);
	ft_putstr_fd (" |_   \\  /   _| (_)           (_)", 1);
	ft_putstr_fd ("         [  |           [  | [  |  \n", 1);
	ft_putstr_fd ("   |   \\/   |   __   _ .--.   __ ", 1);
	ft_putstr_fd ("   .--.   | |--.  .---.  | |  | |  \n", 1);
	ft_putstr_fd ("   | |\\  /| |  [  | [ `.-. | [  |", 1);
	ft_putstr_fd ("  ( (`\\]  | .-. |/ /__\\  | |  | |  \n", 1);
	ft_putstr_fd ("  _| |_\\/_| |_  | |  | | | |  | |", 1);
	ft_putstr_fd ("   `'.'.  | | | || \\__., | |  | |  \n", 1);
	ft_putstr_fd (" |_____||_____|[___][___||__][___]", 1);
	ft_putstr_fd (" [\\__) )[___]|__]'.__.'[___][___] \n", 1);
	ft_putstr_fd ("\x1B[0m \n", 1);
}

char	*last_str(t_env *env)
{
	char	**tmp;
	char	*str;
	size_t	i;

	i = 0;
	if (env_search(env, "PWD=")->content)
	{
		if (env_search(env, "PWD=")->content[0] == '\0')
			return ("/");
		tmp = ft_split(env_search(env, "PWD=")->content, '/');
	}
	else
		tmp = NULL;
	if (tmp == NULL)
		return ("/");
	if (tmp && tmp[0] && tmp[0][0] == '\0')
		return ("/");
	while (tmp[i])
		i++;
	if (i > 0)
		str = ft_strdup(tmp[i - 1]);
	else
		str = ft_strdup("/");
	free_tab(tmp);
	return (str);
}
