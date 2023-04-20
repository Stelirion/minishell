/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:04:58 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/20 18:50:04 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

static int	is_built_in_p(t_param	*param, t_env *env, int *fd, t_pid *pid);

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
	if (param && is_built_in(param, env, give, pid) != 1)
		;
	else
	{
		signal(SIGINT, cancel_commande);
		inception(param->content);
		res_fork = try_exec (env, param);
		close(fd[1]);
		if (res_fork == 0)
			end_of_prog_exit_fd(env, param, 0, give);
	}
	ft_undup(give);
	return (close (fd[0]), close(fd_org[1]), res_fork);
}

int	exec_pure_p(t_env *env, t_param *param, int *fd_org, t_pid *pid)
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
	if (param && is_built_in_p(param, env, give, pid) != 1)
		;
	else
	{
		res_fork = try_exec (env, param);
		close(fd[1]);
		if (res_fork == 0)
			end_of_prog_exit_fd(env, param, 0, give);
	}
	ft_undup(give);
	return (close (fd[0]), close(fd_org[1]), res_fork);
}

static int	is_built_in_p(t_param	*param, t_env *env, int *fd, t_pid *pid)
{
	char	**str;

	(void)fd;
	(void)pid;
	if (!ft_strcmp(param->content, "exit"))
	{
		close (0);
		close (1);
		return (-2);
	}
	else if (!ft_strcmp(param->content, "echo"))
	{
		str = param_to_arg(env, param->next);
		if (!str)
			str[1] = ft_strdup("");
		echo(str);
		free_tab(str);
		return (-2);
	}
	else if (!ft_strcmp(param->content, "cd"))
		return (-2);
	else if (!ft_strcmp(param->content, "env"))
		print_env(env);
	else if (!ft_strcmp(param->content, "pwd"))
		pwd();
	else if (!ft_strcmp(param->content, "export"))
		return (-2);
	else if (!ft_strcmp(param->content, "unset"))
		return (-2);
	else
		return (1);
	return (-2);
}



