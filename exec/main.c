/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:38:47 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/04 14:25:28 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Tools/Libft/libft.h"
#include "minishell.h"


void	free_tab(char **str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i])
			free(str[i]);
	}
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	// t_env	*test;
	char	**str;

	(void)argc;
	// (void)argv;
	g_return_value = 0;
	env = get_env(envp);
	// print_env(env);
	// env_add(env, argv[1]);
	// env = env_unset(env, argv[1]);
		// print_env(env);
	// cd(env, argv[1]);
	// env = env_unset(env, "PWD=");
	// env = env_unset(env, "SHLVL=");
	str = ft_split_shell(argv[1]);
	echo(str);
	free_tab(str);
	// printf("%s\n", env_search(env, "PWD=")->content);
	// printf("\n\n");
	// print_export(env);
	// printf("Done\nNonore a dis de mettre du terreau pour que ca marche\n");
	// print_env(env);
	end_of_prog(env, 0);
	// printf("%p || %p", env_search_less(env, "PATH="), env_search(env, "PATH="));
	// env_add(env, "PATH=cookie");
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