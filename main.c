/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/19 16:24:55 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Tools/Libft/libft.h"
#include "minishell.h"
int	g_return_value;

void	print_params(t_param *list)
{
	printf("_____Debug_____\n");
	while (list)
	{
		printf("%s|%i\n", list->content, list->type);
		list = list->next;
	}
}

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

void new_prompt()
{
	ft_putstr_fd("\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void cancel_commande()
{
	ft_putstr_fd("\n", 1);
	return;
}

int	display(t_env *env, int	*fd_org)
{
	char	*line;
	char	*tmp;
	t_param	*param;
	
	param = NULL;
	tmp = last_str(env);
	line = ft_strjoin ("\x1B[34;1m Minishell : \x1B[35m", tmp);
	free(tmp);
	tmp = ft_strjoin (line, "\x1B[0m : ");
	free(line);
	
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);

	line = readline(tmp);
	signal(SIGINT, cancel_commande);
	free(tmp);
	if (!line)
		return (end_of_prog_exit(env, param, 0), 0);
	
	param = parsing_core(line, param, env);
	if (line && line[0] != '\0')
		add_history(line);
	free(line);
	if (param)
		param = type_setting(param);
	if (param)
	{	
		print_params(param);
		printf("_____________\n");
		exec_core(param, env, fd_org);
	}		
	param_lstclear(&param);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int retry;
	t_env	*env;
	int		fd_org[2];

	(void)argc;
	(void)argv;
	fd_org[0] = dup(0);
	fd_org[1] = dup(1);
	if (fd_org[1] == -1 || fd_org[0] == -1)
		return (1);
	env = get_env(envp);
	header();
	retry = 1;
	
	while (retry)
	{
		retry = display(env, fd_org);
	}
}
