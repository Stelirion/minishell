/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:33:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 21:43:27 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child(t_env *ebv, t_param *param);
static	void	free_tabs(char **a, char **b, char **c);

int	try_exec(t_env *env, t_param *param, t_pid	*pid)
{
	int	res_fork;

	res_fork = fork();
	if (res_fork == -1)
		return (ft_putstr_fd("fork failed\n", 2), -1);
	else if (res_fork == 0)
	{
		pid_clear(pid);
		child(env, param);
	}
	return (res_fork);
}

static void	child(t_env *env, t_param *param)
{
	char	**tmp;
	char	**arg;
	char	**env_a;

	if (env_search(env, "PATH=") == 0 || env_search(env, "PATH=")->content == 0)
		tmp = ft_split("", ':');
	else
		tmp = ft_split(env_search(env, "PATH=")->content, ':');
	if (!tmp)
		error_handler(130, env, param);
	arg = arg_array(env, param);
	env_a = env_to_array(env, param->next);
	if (!access(param->content, X_OK))
		execve(param->content, arg, env_a);
	if (ft_strchr(param->content, '/') == NULL)
		exec_test(tmp, param, arg, env_a);
	else
		exec_test2(env, param, arg, env_a);
	free_tabs(arg, tmp, env_a);
	end_of_prog_exit(env, param, g_return_value);
}

static	void	free_tabs(char **a, char **b, char **c)
{
	free_tab(a);
	free_tab(b);
	free_tab(c);
}

size_t	param_lstsize_arg(t_param *param)
{
	size_t	i;

	i = 0;
	while (param && param->type != PIPE)
	{
		if (param->type == ARG)
			i++;
		param = param->next;
	}
	return (i);
}
