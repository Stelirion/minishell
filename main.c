/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/05 19:29:13 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Tools/Libft/libft.h"
#include "minishell.h"

void	print_params(t_param *list)
{
	printf("_____Debug_____\n");
	while (list)
	{
		printf("%s|%i\n", list->content, list->type);
		list = list->next;
	}
	printf("_______________\n\n");
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
		if (!line)
			return (end_of_prog_exit(env, param, 0), 0);
		param = NULL;
		param = parsing_core(line, param);
		if (line && line[0] != '\0')
			add_history(line);
		if (param)
			param = type_setting(param);
		else if (line && line[0] != '\0')
			ft_putstr_fd ("Error, invalid format\n", 1);
		if (param)	
			// print_params(param);
			exec_core(param, env);
		else if (line && line[0] != '\0')
			ft_putstr_fd ("Error, missing infile/outfile\n", 1);
		
		free(line);
		param_lstclear(&param);
	}
}
