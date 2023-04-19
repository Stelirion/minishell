/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/19 19:28:34 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_param	*param, t_env *env, int *fd, t_pid *pid)
{
	char	**str;

	if (!ft_strcmp(param->content, "exit"))
	{
		close (0);
		close (1);
		pid_clear(pid);
		end_of_prog_exit_fd(env, param, 0, fd);
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
	{
		if (param_lstsize_nb_arg(param) != 1)
			ft_putstr_fd("Minishell : cd take only 1 argument\n", 1);
		else
		{
			if (param->next && param->next->content)
				cd(env, param->next->content);
			else
				cd(env, "");
		}
		return (-2);
	}
	else if (!ft_strcmp(param->content, "env"))
		print_env(env);
	else if (!ft_strcmp(param->content, "pwd"))
		pwd();
	else if (!ft_strcmp(param->content, "export"))
		export_handler(param, env);
	else if (!ft_strcmp(param->content, "unset"))
	{
		while (param->next)
		{
			param = param->next;
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
