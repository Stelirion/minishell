/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/05 16:37:56 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_param	*param, t_env *env)
{
	char	**str;

	if (!ft_strcmp(param->content, "exit"))
		end_of_prog_exit(env, param, 0);
	else if (!ft_strcmp(param->content, "echo"))
	{
		str = param_to_array(env, param->next);
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

void	exec_core(t_param	*param, t_env *env)
{
	int		res_fork;
	int		pipe_fnd;
	t_param	*tmp;
	t_pipe	*spipe;
	
	spipe = malloc(sizeof(t_pipe));
	if (pipe(spipe->second) == -1)
		return (ft_putstr_fd("Error : a pipe didn't work", 2));
	spipe->first[0] = 0;
	spipe->first[1] = 1;
	spipe->counter = 0;
	while (param)
	{
		pipe_fnd = -1;
		tmp = param;
		while (tmp)
		{
			if (tmp->type == PIPE)
			{
				// ft_pipe(param, env, spipe);
				spipe->counter++;
				pipe_fnd = fork();
				break ;
			}
			tmp = tmp->next;
			pipe_fnd = -2;
		}
		if (pipe_fnd == 0 || pipe_fnd == -2)
		{
			if (!param)
			{
				if (!res_fork)
					ft_putstr_fd("No command found\n", 2);
				break ;
			}
			if (param && is_built_in(param, env) != 1)
				;
			else
				res_fork = try_exec (env, param);
		}
		if (pipe_fnd == 0)
		{
			close (spipe->second[0]);
			close (spipe->second[1]);
			close (spipe->first[0]);
			close (spipe->first[1]);
			end_of_prog_exit(env, param, g_return_value);
		}
		param = param->next;
		while (param && param->type != CMD)
			param = param->next;
	}
	close (spipe->second[0]);
	close (spipe->second[1]);
	// close (spipe->first[0]);
	// close (spipe->first[1]);
	free(spipe);
	if (pipe_fnd)
		waitpid(pipe_fnd, 0, 0);
	if (res_fork != -1)
		waitpid(res_fork, 0, 0);
}
