/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:43:43 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 17:57:44 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_cmd_not_found(char *str);

char	**arg_array(t_env *env, t_param *param)
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
			free(cmd);
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
	g_return_value = 127;
	if (!access(cmd, F_OK))
		g_return_value = 126;
	free(cmd);
	print_cmd_not_found(param->content);
}

static void	print_cmd_not_found(char *str)
{
	ft_putstr_fd("Minishell : command not found : ", 2);
	ft_putstr_fd(str, 2);
	write (2, "\n", 1);
}
