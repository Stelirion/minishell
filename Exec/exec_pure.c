/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:04:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/01 20:50:21 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_built_in_p(t_param	*param, t_env *env, int *fd, t_pid *pid);
static int	echo_built_in(t_param	*param, t_env *env);
static void	export_handler2(t_param *param, t_env *env);

int	exec_pure(t_env *env, t_param *param, int *fd_org, t_pid *pid)
{
	int	res_fork;
	int	fd[2];
	int	give[4];

	res_fork = -2;
	fd[0] = dup(fd_org[0]);
	fd[1] = dup(fd_org[1]);
	give[0] = fd_org[1];
	give[1] = fd_org[0];
	give[2] = fd[1];
	give[3] = fd[0];
	if (!ft_redirect(param, fd))
		return (0);
	while (param && param->type != CMD)
		param = param->next;
	if (!(param && is_built_in(param, env, give, pid) != 1))
	{
		inception(param->content);
		res_fork = try_exec (env, param, pid);
		close(fd[1]);
		if (res_fork == 0)
			end_of_prog_exit_fd(env, param, 0, give);
	}
	return (ft_undup(give), close (fd[0]), close(fd_org[1]), res_fork);
}

int	exec_pure_p(t_env *env, t_param **param, int *fd_org, t_pid *pid)
{
	int	res_fork;
	int	fd[2];
	int	give[4];

	res_fork = -2;
	fd[0] = dup(fd_org[0]);
	fd[1] = dup(fd_org[1]);
	give[0] = fd_org[1];
	give[1] = fd_org[0];
	give[2] = fd[1];
	give[3] = fd[0];
	if (!ft_redirect(param[0], fd))
		return (0);
	exec_order(param[0]);
	while (param && param[0]->type != CMD)
		param[0] = param[0]->next;
	if (!(param && is_built_in_p(param[0], env, give, pid) != 1))
	{
		res_fork = try_exec (env, param[0], pid);
		close(fd[1]);
		if (res_fork == 0)
			end_of_prog_exit_fd(env, param[1], 0, give);
	}
	ft_undup(give);
	return (close (fd[0]), close(fd_org[1]), res_fork);
}

static int	is_built_in_p(t_param	*param, t_env *env, int *fd, t_pid *pid)
{
	(void)fd;
	(void)pid;
	if (!ft_strcmp(param->content, "exit"))
	{
		close (0);
		close (1);
		return (-2);
	}
	else if (!ft_strcmp(param->content, "echo"))
		return (echo_built_in (param, env));
	else if (!ft_strcmp(param->content, "cd"))
		return (-2);
	else if (!ft_strcmp(param->content, "env"))
		print_env(env);
	else if (!ft_strcmp(param->content, "pwd"))
		pwd();
	else if (!ft_strcmp(param->content, "export"))
		return (export_handler2(param, env), 1);
	else if (!ft_strcmp(param->content, "unset"))
		return (-2);
	else
		return (1);
	return (-2);
}

static int	echo_built_in(t_param	*param, t_env *env)
{
	char	**str;

	str = param_to_arg(env, param->next);
	if (!str)
		str[1] = ft_strdup("");
	echo(str);
	free_tab(str);
	return (-2);
}

static void	export_handler2(t_param *param, t_env *env)
{
	char	**str;

	str = param_to_array(env, param);
	(void) env;
	if (!str)
		error_handler(130, env, param);
	if (!str[1] || str[1][0] == '\0')
	{
		print_export(env);
	}
	free_tab(str);
	g_return_value = 0;
}
