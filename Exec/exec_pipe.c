/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:58:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 21:41:56 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				*ft_pipe3(t_param *param, int *i, int j);
int				check_pipe(t_param *param);
static	t_pipe	fill(t_pipe pipe, int i[2], int j[2]);
static void		pipe_child(t_env *env, t_param *param, t_pid *pid, \
			int **fd_tmp);

void	handle_pipe(t_env *env, t_param *param, int *fd_org, t_pid	*pid)
{
	int		fd[2];
	t_pipe	pipe;

	pipe = fill(pipe, fd, fd_org);
	while (param)
	{
		while (param && param->type != CMD)
			param = param->next;
		if (!param)
			break ;
		signal(SIGINT, cancel_commande);
		inception(param->content);
		if (check_pipe(param))
			pid_lstadd_back(&pid, pid_lstnew
				(exec_pipe(env, param, pipe, pid)));
		else
			pid_lstadd_back(&pid, pid_lstnew(exec_pure_p(env, \
				param, fd_org, pid)));
		param = param->next;
	}
}

int	exec_pipe(t_env *env, t_param *param, t_pipe spipe, t_pid	*pid)
{
	int	res_fork;
	int	*fd;
	int	*fd_org;
	int	*fd_tmp[2];

	fd = spipe.first;
	fd_org = spipe.second;
	pipe(fd);
	res_fork = fork();
	if (res_fork == 0)
	{	
		fd_tmp[0] = fd;
		fd_tmp[1] = fd_org;
		pipe_child(env, param, pid, fd_tmp);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	close(fd_org[1]);
	return (res_fork);
}

static t_pipe	fill(t_pipe pipe, int i[2], int j[2])
{
	pipe.first[0] = i[0];
	pipe.first[1] = i[1];
	pipe.second[0] = j[0];
	pipe.second[1] = j[1];
	return (pipe);
}

int	check_pipe(t_param *param)
{
	t_param	*tmp;

	tmp = param;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	pipe_child(t_env *env, t_param *param, t_pid	*pid, int **fd_tmp)
{
	int	res_fork;

	dup2(fd_tmp[0][1], 1);
	if (!ft_redirect(param, fd_tmp[0]))
		return (end_of_prog_exit(env, param, 0), (void)1);
	close(fd_tmp[0][1]);
	close(fd_tmp[0][0]);
	close(fd_tmp[1][0]);
	close(fd_tmp[1][1]);
	if (param && is_built_in(param, env, fd_tmp[0], pid) != 1)
		;
	else
		res_fork = try_exec (env, param, pid);
	close (1);
	waitpid(res_fork, 0, 0);
	pid_clear(pid);
	g_return_value = res_fork;
	end_of_prog_exit(env, param, 0);
}
