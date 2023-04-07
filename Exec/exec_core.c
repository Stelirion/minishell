/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/07 13:51:07 by mbrement         ###   ########lyon.fr   */
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

void	exec_core(t_param	*param, t_env *env)
{
	int		pipe_fnd;
	t_param	*tmp;

	tmp = param;
	pipe_fnd = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe_fnd++;
		tmp = tmp->next;
	}
	if (pipe_fnd != 0)
		exec_pipe(env, param);
	else
		exec_pure(env, param);
}
