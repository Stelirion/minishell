/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:33:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/14 10:39:30 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child(t_env *ebv, t_param *param);
static char	**arg_array(t_env *env, t_param *param);

int	try_exec(t_env *env, t_param *param)
{
	int	res_fork;

	res_fork = fork();
	if (res_fork == -1)
		return (ft_putstr_fd("fork failed\n", 2), -1);
	else if (res_fork == 0)
		child(env, param);
	return (res_fork);
}

static void	child(t_env *env, t_param *param)
{
	char	**tmp;
	char	**arg;
	char	**env_a;
	char	*cmd[2];
	size_t	i;
	// struct	stat *whydoiexist;

	// whydoiexist = malloc(sizeof (struct stat));
	tmp = ft_split(env_search(env, "PATH=")->content, ':');
	i = -1;
	arg = arg_array(env, param);
	env_a = env_to_array(env, param->next);
	if (!access(param->content, X_OK))
		execve(param->content, arg, env_a);
	if (ft_strchr(param->content, '/') == NULL)
	{
		while (tmp[++i])
		{
			cmd[0] = ft_strjoin(tmp[i], "/");
			cmd[1] = ft_strjoin(cmd[0], param->content);
			if (!access(cmd[1], X_OK))
				execve(cmd[1], arg, env_a);
			free(cmd[0]);
			free(cmd[1]);
		}
		// ft_putstr_fd(strerror(errno), 2);
		// write (2, "\n", 1);
		ft_putstr_fd("Minishell : command not found : ", 2);
		ft_putstr_fd(param->content, 2);
		write (2, "\n", 1);
	}
	else
	{
		cmd[0] = ft_strjoin(env_search(env, "PWD=")->content, "/");
		cmd[1] = ft_strjoin(cmd[0], param->content);
		if (access(cmd[1], X_OK))
			execve(cmd[1], arg, env_a);
		free(cmd[0]);
		free(cmd[1]);
		// if (stat(cmd[1], whydoiexist))
		// {
		// 	ft_putstr_fd(strerror(errno), 2);
		// 	write (2, "\n", 1);
		// }
		ft_putstr_fd("Minishell : command not found : ", 2);
		ft_putstr_fd(param->content, 2);
		write (2, "\n", 1);
	}
	free_tab(arg);
	free_tab(tmp);
	free_tab (env_a);
	// free(whydoiexist);
	// end_of_prog_exit(env, param, 2);
	return ;
}

static size_t	param_lstsize_arg(t_param *param)
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

static char	**arg_array(t_env *env, t_param *param)
{
	char	**str;
	char	*tmp;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char *) * (param_lstsize_arg(param) + 2));
	if (!str)
		error_handler(130, env, param);
	while (param && param->type != PIPE)
	{
		if (param->type == ARG || param->type == CMD)
		{
			tmp = ft_strdup(param->content);
			if (!tmp)
				error_handler(130, env, param);
			str[i] = tmp;
			i++;
		}
		param = param->next;
	}
	str[i] = NULL;
	return (str);
}
