/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:33:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 17:27:51 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>

static void	child(t_env *ebv, t_param *param);
static char	**arg_array(t_env *env, t_param *param);
static	void	free_tabs(char **a, char **b, char **c);
void		print_cmd_not_found(char *str);
void		exec_test(char **tmp, t_param *param, char **arg, char **env_a);
void		exec_test2(t_env *env, t_param *param, char **arg, char **env_a);

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

void	print_cmd_not_found(char *str)
{
	ft_putstr_fd("Minishell : command not found : ", 2);
	ft_putstr_fd(str, 2);
	write (2, "\n", 1);
}

static	void	free_tabs(char **a, char **b, char **c)
{
	free_tab(a);
	free_tab(b);
	free_tab(c);
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

void	exec_test(char **tmp, t_param *param, char **arg, char **env_a)
{
	size_t	i;
	char	*cmd;

	i = -1;
	while (tmp && tmp[++i])
	{
		cmd = ft_strjoin(tmp[i], "/");
		cmd = ft_strjoin_free(cmd, param->content);
		if (!access(cmd, X_OK))
			execve(cmd, arg, env_a);
		if (!access(cmd, F_OK))
		{
			g_return_value = 126;
			break ;
		}
		free(cmd);
	}
	g_return_value = 127;
	print_cmd_not_found(param->content);
}

void	exec_test2(t_env *env, t_param *param, char **arg, char **env_a)
{
	char	*cmd;

	cmd = ft_strjoin(env_search(env, "PWD=")->content, "/");
	cmd = ft_strjoin_free(cmd, param->content);
	if (access(cmd, X_OK))
		execve(cmd, arg, env_a);
	if (!access(cmd, F_OK))
		g_return_value = 126;
	free(cmd);
	g_return_value = 127;
	print_cmd_not_found(param->content);
}
