/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:58:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/11 11:40:26 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>


int	*ft_pipe3(t_param *param, int *i, int j);
int	check_pipe(t_param *param);

void	handle_pipe(t_env *env, t_param *param, int *fd_org)
{
	int		fd[2];

	while (param)
	{
		while (param && param->type != CMD)
			param = param->next;
		if (!param)
			break ;
		if (check_pipe(param))
			exec_pipe(env, param, fd, fd_org);
		else
		{
			exec_pure(env, param, fd_org);
		}
		param = param->next;
	}
}

void	exec_pipe(t_env *env, t_param *param, int *fd, int *fd_org)
{
	// int		redirection[2];

	pipe(fd);
	if (!fork())
	{
		dup2(fd[1], 1);
		ft_redirect(param, fd);
		close(fd[1]);
		close(fd[0]);
		close(fd_org[0]);
		close(fd_org[1]);
		if (param && is_built_in(param, env) != 1)
			;
		else
			(void)try_exec (env, param);
		close (1);
		end_of_prog_exit(env, param, 0);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	close(fd_org[1]);
}
// void	exec_pipe3(t_env *env, t_param *param)
// {
// 	int	res_fork[2];
// 	int	fd[4];
// 	int	piped[2];
// 	// int	piped_child[2];
// 	// int	i;

// 	res_fork[0] = -2;
// 	// i = 0;
// 	pipe(piped);
// 	fd[2] = dup(0);
// 	fd[3] = dup(1);
// 	res_fork[1] = fork();
// 	if (res_fork[1] == 0)
// 	{
// 		(void)ft_pipe3(param, piped, 0);
// 		while (param)
// 		{
// 			// if (i == 0)
// 			// 	close(piped[0]);
// 			// i = 1;
// 			while (param && param->type != CMD)
// 				param = param->next;
// 			if (!param)
// 				break ;
// 			ft_redirect(param, fd);
// 			if (param && is_built_in(param, env) != 1)
// 				;
// 			else
// 				res_fork[0] = try_exec (env, param);
// 			param = param->next;
// 			ft_undup(fd);
// 			(void)ft_pipe3(param, piped, 0);
// 		}
// 		end_of_prog_exit(env, param, 0);
// 	}
// 	else if (res_fork[1] == -1)
// 		ft_putstr_fd("Fork didn't work", 2);
// 	else
// 	{
// 		dup2(fd[2], piped[0]);
// 		close(piped[1]);
// 		waitpid(res_fork[1], 0, 0);
// 	}
// }

// int	*ft_pipe3(t_param *param, int *piped, int j)
// {
// 	t_param	*tmp;
// 	int		flag;

// 	tmp = param;
// 	(void) j;
// 	flag = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 			flag = 1;
// 		tmp = tmp->next;
// 	}
// 	if (!flag)
// 	{
// 		close (piped[0]);
// 		dup2(piped[1], 1);
// 		close(piped[1]);
// 	}
// 	// if (flag && j != 1)
// 	// {
// 		// dup2(piped[0], 0);
// 	// }
// 	return (piped);
// }

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