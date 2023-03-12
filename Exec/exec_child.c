/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:33:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/12 15:07:11 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child(t_env *ebv, t_param *param);
static char	**arg_array(t_env *env, t_param *param);

t_param	*try_exec(t_env *env, t_param *param)
{
	int	res_fork;

	res_fork = fork();
	if (res_fork == -1)
		return (ft_putstr_fd("fork failed\n", 2), param);
	if (res_fork == 0)
		child(env, param);
	else
		waitpid(res_fork, 0, 0);
	return (param->next);
}

static void	child(t_env *env, t_param *param)
{
	char	**tmp;
	char	**arg;
	char	**env_a;
	char	*cmd[2];
	size_t	i;

	tmp = ft_split(env_search(env, "PATH=")->content, ':');
	i = -1;
	arg = arg_array(env, param->next);
	env_a = env_to_array(env, param->next);
	while (tmp[++i])
	{
		cmd[0] = ft_strjoin(tmp[i], "/");
		cmd[1] = ft_strjoin(cmd[0], param->content);
		execve(cmd[1], arg, env_a);
		free(cmd[0]);
		free(cmd[1]);
	}
	free_tab(arg);
	free_tab(tmp);
	free_tab (env_a);
	ft_putstr_fd("Minishell : command not found: ", 2);
	ft_putstr_fd(param->content, 2);
	write (2, "\n", 1);
	end_of_prog_exit(env, param, 2);
}

static char	**arg_array(t_env *env, t_param *param)
{
	char	**str;
	char	*tmp;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char *) * (param_lstsize(param) + 1));
	if (!str)
		error_handler(130, env, param);
	while (param && param->type == ARG)
	{
		tmp = ft_strdup(param->content);
		if (!tmp)
			error_handler(130, env, param);
		str[i] = tmp;
		param = param->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
