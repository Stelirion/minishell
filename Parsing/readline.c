/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:19:56 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/04 15:04:59 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	print_params(t_param *list)
// {
// 	while (list)
// 	{
// 		ft_putstr_fd(list->content, 1);
// 		ft_putchar_fd('\n', 1);
// 		list = list->next;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	size_t	i;
// 	size_t	start;
// 	char	*line;
// 	char	*new_str;
// 	t_param	*param;
// 	t_param	*new_lst;

// 	ft_putstr_fd (" ____    ____   _             _          __             __   __   \n", 1);
// 	ft_putstr_fd ("|_   \\  /   _| (_)           (_)        [  |           [  | [  |  \n", 1);
// 	ft_putstr_fd ("  |   \\/   |   __   _ .--.   __   .--.   | |--.  .---.  | |  | |  \n", 1);
// 	ft_putstr_fd ("  | |\\  /| |  [  | [ `.-. | [  | ( (`\\]  | .-. |/ /__\\  | |  | |  \n", 1);
// 	ft_putstr_fd (" _| |_\\/_| |_  | |  | | | |  | |  `'.'.  | | | || \\__., | |  | |  \n", 1);
// 	ft_putstr_fd ("|_____||_____|[___][___||__][___][\\__) )[___]|__]'.__.'[___][___] \n", 1);
// 	while (1)
// 	{
// 		line = readline("Enter a line: ");
// 		i = 0;
// 		param = param_lstnew("NULL");
// 		while (line[i])
// 		{
// 			while (line[i] == ' ')
// 				i++;
// 			start = i;
// 			if (line[i] == '\'')
// 			{
// 				i++;
// 				while (line[i] && line[i] != '\'')
// 					i++;
// 				if (!line[i] && line[i] != '\'')
// 					error_handler(0);
// 				new_str = ft_substr(line, start + 1, i - start - 1);
// 			}
// 			else if (line[i] == '"')
// 			{
// 				i++;
// 				while (line[i] && line[i] != '"')
// 					i++;
// 				if (!line[i] && line[i] != '"')
// 					error_handler(0);
// 				new_str = ft_substr(line, start + 1, i - start - 1);
// 			}
// 			else
// 			{
// 				while (line[i + 1] && line[i] != ' ')
// 					i++;
// 				new_str = ft_substr(line, start, i - start + 1);
// 			}
// 			i++;
// 			new_lst = param_lstnew(new_str);
// 			param_lstadd_back(&param, new_lst);
// 		}
// 		new_lst = param->next;
// 		free(param);
// 		print_params(new_lst);
// 		param_lstclear(&new_lst);
// 	}
// }
