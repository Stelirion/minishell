/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:38:47 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 17:49:26 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	// t_env	*test;

	(void)argc;
	(void)argv;
	g_return_value = 0;
	env = get_env(envp);
	// print_env(env);
	// env_add(env, "PATH=hi");
	// print_env(env);
	end_of_prog(env, 0);
	// printf("%p || %p", env_search_less(env, "PATH="), env_search(env, "PATH="));
	// env_add(env, "PATH=cookie");
	// print_env(env);
	// end_of_prog(env, 0);
	// (void)env;env
	// test = env_search(env, argv[1]);
	// if (test)
	// 	printf("\n\n%s%s\n\n", test->name, test->content);
	// else
	// 	printf("failed");
	// env_change(argv[1], argv[2], env);
	// test = env_search(env, argv[1]);
	// if (test)
	// 	printf("\n\n%s%s\n\n", test->name, test->content);
	// else
	// 	printf("failed");
}

	// (void)env;
	// printf("%s", argv[0]);
	// printf("%s", env->next->name);
	// printf("%s\n", env);
	// printf("done, IT WORK BITCH");
	// printf("name : %s\ncontent : %s\n", env->name, env->content);