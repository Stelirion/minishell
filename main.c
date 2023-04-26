/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:20:20 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/26 16:29:48 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return_value;

int	launchpad(char *line, t_env *env, char *tmp, int *fd_org)
{
	t_param	*param;

	param = NULL;
	signal(SIGINT, cancel_commande);
	signal(SIGQUIT, command_back);
	if (!line)
		return (end_of_prog_exit(env, param, 0), 1);
	if (!token_format(line))
		return (parsing_error(6), free(line), 1);
	param = parsing_core(line, param, env);
	if (line && line[0] != '\0')
		add_history(line);
	free(line);
	if (param)
		param = type_setting(param);
	if (param)
		param = manage_dock(param, env);
	if (param)
		exec_core(param, env, fd_org);
	param_lstclear(&param);
	tmp = ft_itoa(g_return_value);
	env_change("?=", tmp, env);
	return (1);
}

int	display(t_env *env, int	*fd_org)
{
	char	*line;
	char	*tmp;

	g_return_value = 0;
	tmp = last_str(env);
	line = ft_strjoin ("\x1B[34;1m Minishell : \x1B[35m", tmp);
	free(tmp);
	tmp = ft_strjoin (line, "\x1B[0m : ");
	free(line);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	line = readline(tmp);
	free(tmp);
	launchpad(line, env, tmp, fd_org);
	return (1);
}
static t_env	*add_dummy(t_env *env);

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
	env = add_dummy(env);
	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup("?=");
	tmp[1] = ft_strdup("0");
	if (!tmp || !tmp[0] || !tmp[1])
		return (ft_putstr_fd("Couldn't start\n", 2), free_tab(tmp), 1);
	env_lstadd_back(&env, env_lstnew(tmp));
	free(tmp);
	header();
	retry = 1;
	while (retry)
		retry = display(env, fd_org);
}

static t_env	*add_dummy(t_env *env)
{
	char	**tmp;
	t_env	*new;

	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		exit(1);
	tmp[1] = "0";
	tmp[0] = "0";
	new = env_lstnew(tmp);
	if (!new)
		exit(1);
	env_lstadd_front(&env, new);
	new = env_lstnew(tmp);
	if (!new)
		exit(1);
	env_lstadd_front(&env, new);
	free(tmp);
	return (env);
}
