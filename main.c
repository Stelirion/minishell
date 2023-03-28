/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/28 09:34:03 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_params(t_param *list)
{
	while (list)
	{
		printf("%s | %i\n", list->content, list->type);
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
		tmp = last_str(env);
		line = ft_strjoin ("\x1B[34;1m Minishell : \x1B[35m", tmp);
		free(tmp);
		tmp = ft_strjoin (line, "\x1B[0m : ");
		free(line);
		line = readline(tmp);
		free(tmp);
		param = NULL;
		param = parsing_core(line, param);
		add_history(line);
		free(line);
		if (param)
		{
			type_setting(param);
			print_params(param);
			exec_core(param, env);
		}
		else
			ft_putstr_fd ("Error, invalid format\n", 1);
		param_lstclear(&param);
	}
}
