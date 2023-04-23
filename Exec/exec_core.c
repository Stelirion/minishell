/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/23 02:14:20 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		arg_exit(t_param *param, t_env *env, int *fd, t_pid *pid);
static	void	not_numerical(t_param *param, t_env *env, int *fd);
int			cd_built_in(t_param	*param, t_env *env);
int			echo_built_int(t_param	*param, t_env *env);

int	is_built_in(t_param	*param, t_env *env, int *fd, t_pid *pid)
{
	if (!ft_strcmp(param->content, "exit"))
		return (close (0), close (1), arg_exit(param, env, fd, pid), -2);
	else if (!ft_strcmp(param->content, "echo"))
		return (echo_built_int(param, env));
	else if (!ft_strcmp(param->content, "cd"))
		return (cd_built_in(param, env));
	else if (!ft_strcmp(param->content, "env"))
		print_env(env);
	else if (!ft_strcmp(param->content, "pwd"))
		pwd();
	else if (!ft_strcmp(param->content, "export"))
		export_handler(param, env);
	else if (!ft_strcmp(param->content, "unset"))
	{
		while (param->next && param->type != PIPE)
		{
			param = param->next;
			if (param->type == ARG)
				env = env_unset(env, param->content);
		}
	}
	else
		return (1);
	return (-2);
}

void	exec_core(t_param	*param, t_env *env, int *fd_org)
{
	int		pipe_fnd;
	t_param	*tmp;
	t_pid	*pid;

	pid = pid_lstnew(-2);
	tmp = param;
	pipe_fnd = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe_fnd++;
		tmp = tmp->next;
	}
	if (pipe_fnd != 0)
		handle_pipe(env, param, fd_org, pid);
	else
		pid_lstadd_back(&pid, pid_lstnew(exec_pure(env, param, fd_org, pid)));
	dup2(fd_org[0], 0);
	dup2(fd_org[1], 1);
	waiting(pid);
}

void	arg_exit(t_param *param, t_env *env, int *fd, t_pid *pid)
{
	size_t	i;
	t_param	*tmp;

	i = 0;
	tmp = param;
	write(2, "exit\n", 5);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			i++;
		tmp = tmp->next;
	}
	if (i > 1)
		return (ft_putstr_fd("exit : Too many arguments\n", 2), (void)0);
	pid_clear(pid);
	tmp = param;
	while (i == 1 && tmp->type != ARG)
		tmp = tmp->next;
	i = 0;
	if (tmp->content && ft_isdigit_str(tmp->content))
		end_of_prog_exit_fd(env, param, ft_atoi(tmp->content) % 256, fd);
	if (tmp->content && tmp->type == 4)
		not_numerical(param, env, fd);
	end_of_prog_exit_fd(env, param, g_return_value, fd);
}

static	void	not_numerical(t_param *param, t_env *env, int *fd)
{
	ft_putstr_fd("exit take only numerical argument\n", 2);
	end_of_prog_exit_fd(env, param, 0, fd);
}

int	cd_built_in(t_param	*param, t_env *env)
{
	if (param_lstsize_nb_arg(param) > 1)
		ft_putstr_fd("Minishell : cd take only 1 argument\n", 1);
	else if (param_lstsize_nb_arg(param) == 0)
	{
		if (env_search(env, "HOME=") == 0 || \
				!env_search(env, "HOME=")->content)
			ft_putstr_fd("HOME unset\n", 2);
		else
			cd(env, env_search(env, "HOME=")->content);
	}
	else
	{
		if (param->next && param->next->content)
			cd(env, param->next->content);
		else
			cd(env, "");
	}
	return (-2);
}
