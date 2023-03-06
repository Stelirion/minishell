/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:38:47 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/06 13:21:54 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Tools/Libft/libft.h"
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

int	main(int argc, char **argv, char **envp)
{
	size_t	i;
	size_t	start;
	char	*line;
	char	*new_str;
	t_param	*param;
	t_param	*new_lst;
	t_env	*env;

	ft_putstr_fd (" ____    ____   _             _          __             _   __   \n", 1);
	ft_putstr_fd ("|_   \\  /   _| (_)           (_)        [  |           [  | [  |  \n", 1);
	ft_putstr_fd ("  |   \\/   |   __   _ .--.   __   .--.   | |--.  .---.  | |  | |  \n", 1);
	ft_putstr_fd ("  | |\\  /| |  [  | [ `.-. | [  | ( (`\\]  | .-. |/ /__\\  | |  | |  \n", 1);
	ft_putstr_fd (" _| |_\\/_| |_  | |  | | | |  | |  `'.'.  | | | || \\__., | |  | |  \n", 1);
	ft_putstr_fd ("|_____||_____|[___][___||__][___][\\__) )[___]|__]'.__.'[___][___] \n", 1);
	(void)argc;
	(void)argv;
	env = get_env(envp);
	while (1)
	{
		line = readline("Enter a line: ");
		i = 0;
		param = param_lstnew(NULL); //SWAP 
		while (line[i])
		{
			while (line[i] == ' ')
				i++;
			start = i;
			if (line[i] == '\'')
			{
				i++;
				while (line[i] && line[i] != '\'')
					i++;
				if (!line[i] && line[i] != '\'')
					error_handler(130);
				new_str = ft_substr(line, start + 1, i - start - 1);
			}
			else if (line[i] == '"')
			{
				i++;
				while (line[i] && line[i] != '"')
					i++;
				if (!line[i] && line[i] != '"')
					error_handler(130);
				new_str = ft_substr(line, start + 1, i - start - 1); //LEAKS
			}
			else
			{
				while (line[i + 1] && line[i] != ' ')
					i++;
				new_str = ft_substr(line, start, i - start + 1); //LEAKS
			}
			i++;
			new_lst = param_lstnew(new_str);
			param_lstadd_back(&param, new_lst);
		}
		new_lst = param->next;
		free(param);
		exec_core(new_lst, env);
		param_lstclear(&new_lst);
	}
}


// void	free_tab(char **str)
// {
// 	size_t	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i])
// 			free(str[i]);
// 	}
// 	free(str);
// }
// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
// 	// t_env	*test;
// 	char	**str;

// 	(void)argc;
// 	// (void)argv;
// 	g_return_value = 0;
// 	env = get_env(envp);
// 	// print_env(env);
// 	// env_add(env, argv[1]);
// 	// env = env_unset(env, argv[1]);
// 		// print_env(env);
// 	// cd(env, argv[1]);
// 	// env = env_unset(env, "PWD=");
// 	// env = env_unset(env, "SHLVL=");
// 	str = ft_split_shell(argv[1]);
// 	echo(str);
// 	free_tab(str);
// 	// printf("%s\n", env_search(env, "PWD=")->content);
// 	// printf("\n\n");
// 	// print_export(env);
// 	// printf("Done\nNonore a dis de mettre du terreau pour que ca marche\n");
// 	// print_env(env);
// 	end_of_prog(env, 0);
// 	// printf("%p || %p", env_search_less(env, "PATH="), env_search(env, "PATH="));
// 	// env_add(env, "PATH=cookie");
// 	// end_of_prog(env, 0);
// 	// (void)env;env
// 	// test = env_search(env, argv[1]);
// 	// if (test)
// 	// 	printf("\n\n%s%s\n\n", test->name, test->content);
// 	// else
// 	// 	printf("failed");
// 	// env_change(argv[1], argv[2], env);
// 	// test = env_search(env, argv[1]);
// 	// if (test)
// 	// 	printf("\n\n%s%s\n\n", test->name, test->content);
// 	// else
// 	// 	printf("failed");
// }

// 	// (void)env;
// 	// printf("%s", argv[0]);
// 	// printf("%s", env->next->name);
// 	// printf("%s\n", env);
// 	// printf("done, IT WORK BITCH");
// 	// printf("name : %s\ncontent : %s\n", env->name, env->content);