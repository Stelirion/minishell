/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/20 02:03:14 by ngennaro         ###   ########.fr       */
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
		printf("%s|%i", list->content, list->type);
		if (list->type == 7)
			printf("|%i", list->heredoc_fd);
		printf("\n");
		list = list->next;
	}
	printf("_______________\n");
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
		param = manage_dock(param, env);
	if (param)
	{
		print_params(param);
		exec_core(param, env, fd_org);
	}	
	param_lstclear(&param);
	tmp = ft_itoa(g_return_value);
	env_change("?", tmp, env);
	free(tmp);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		retry;
	t_env	*env;
	int		fd_org[2];
	char	**tmp;

	(void)argc;
	(void)argv;
	fd_org[0] = dup(0);
	fd_org[1] = dup(1);
	if (fd_org[1] == -1 || fd_org[0] == -1)
		return (1);
	env = get_env(envp);
	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup("?=");
	tmp[1] = ft_strdup("0");
	env_lstadd_back(&env, env_lstnew(tmp));
	header();
	retry = 1;
	while (retry)
		retry = display(env, fd_org);
}
