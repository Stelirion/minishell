/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/09 14:30:37 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_params(t_param *list)
{
	while (list)
	{
		ft_putstr_fd(list->content, 1);
		ft_putchar_fd('\n', 1);
		list = list->next;
	}
}

void	header(void)
{
	ft_putstr_fd (" ____    ____   _             _  ", 1);
	ft_putstr_fd ("        __             _   __   \n", 1);
	ft_putstr_fd ("|_   \\  /   _| (_)           (_)", 1);
	ft_putstr_fd ("        [  |           [  | [  |  \n", 1);
	ft_putstr_fd ("  |   \\/   |   __   _ .--.   __ ", 1);
	ft_putstr_fd ("  .--.   | |--.  .---.  | |  | |  \n", 1);
	ft_putstr_fd ("  | |\\  /| |  [  | [ `.-. | [  |", 1);
	ft_putstr_fd (" ( (`\\]  | .-. |/ /__\\  | |  | |  \n", 1);
	ft_putstr_fd (" _| |_\\/_| |_  | |  | | | |  | |", 1);
	ft_putstr_fd ("  `'.'.  | | | || \\__., | |  | |  \n", 1);
	ft_putstr_fd ("|_____||_____|[___][___||__][___]", 1);
	ft_putstr_fd ("[\\__) )[___]|__]'.__.'[___][___] \n", 1);
}

#include <limits.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_param	*param;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	header();
	while (1)
	{
		line = readline("Enter a line: ");
		param = NULL;
		param = parsing_core(line, param);
		if (param)
			exec_core(param, env);
		else
			ft_putstr_fd ("Error, invalid format\n", 1);
		param_lstclear(&param);
	}
}
