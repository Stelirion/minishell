/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/28 01:14:56 by mbrement         ###   ########lyon.fr   */
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
		return (g_return_value);
	}
	else if (!ft_strcmp(param->content, "cd"))
	{
		if (param_lstsize(param) > 2)
			ft_putstr_fd("Minishell : cd took only 1 argument\n", 1);
		else
		{
			if (param->next && param->next->content)
				cd(env, param->next->content);
			else
				cd(env, "");
		}
		return (g_return_value);
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
	return (g_return_value);
}

void	exec_core(t_param	*param, t_env *env)
{
	int	res_fork;
	int	i;

	i = 0;
	while (param)
	{
		while (param && param->type != CMD)
			param = param->next;
		if (!param)
		{
			ft_putstr_fd("No command find\n", 2);
			break ;
		}
		if (param && !is_built_in(param, env))
			return ;
		else
			res_fork = try_exec (env, param);
		param = param->next;
	}
	i++;
	if (res_fork != -1)
		waitpid(res_fork, 0, 0);
}
