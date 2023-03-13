/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/13 13:22:19 by mbrement         ###   ########lyon.fr   */
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
	ft_putstr_fd ("\x1B[32;1m  ____    ____   _             _  ", 1);
	ft_putstr_fd ("         __             _   __   \n", 1);
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*tmp;
	t_param	*param;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	header();
	while (1)
	{
		ft_putstr_fd("\x1B[34;1m Minishell : ", 1);
		tmp = last_str(env);
		line = ft_strjoin ("\x1B[35m", tmp);
		free(tmp);
		ft_putstr_fd(line, 1);
		ft_putstr_fd ("\x1B[0m :", 1);
		free (line);
		line = readline(" ");
		param = NULL;
		param = parsing_core(line, param);
		if (param)
			exec_core(param, env);
		else
			ft_putstr_fd ("Error, invalid format\n", 1);
		param_lstclear(&param);
		add_history(line);
		free(line);
	}
}
