/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_old.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:48:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/02 19:16:31 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cd_slash(t_env *env, char *str)
{
	if (chdir(str) == -1)
	{
		ft_putstr_fd("Minishell : cd : ", 1);
		ft_putstr_fd(strerror(errno), 1);
		write (1, "\n", 1);
		g_return_value = 1;
		return ;
	}
	free(env_search(env, "PWD=")->content);
	env_search(env, "PWD=")->content = ft_strdup(str);
	g_return_value = 0;
}

char	*make_path(t_env *env, char **str)
{
	char	**pwd;
	char	*rtn;
	char	*tmp;
	void	*open;
	size_t	i;

	i = -1;
	tmp = malloc(1);
	pwd = ft_split(env_search(env, "PWD=")->content, '/');
	while (str[++i])
	{
		free(tmp);
		if (!ft_strncmp(str[i], ".", 1) && str[i][1] == '\0')
			rtn = merge_tab_char_add(pwd, "/");
		else if (!ft_strncmp(str[i], "..", 1) && str[i][2] == '\0')
		{
			if (str[i] != NULL)
				rtn = merge_tab_char_add_minus(pwd, "/");
			else
			 	rtn = ft_strdup("\0");
		}
		else
		{
			rtn = merge_tab_char_add(pwd, "/");
			tmp = ft_strjoin(rtn, "/");
			free(rtn);
			rtn = ft_strjoin(tmp, str[i]);
			free(tmp);
		}
		tmp = ft_strjoin("/", rtn);
		free(rtn);
		open = opendir(tmp);
		if (!open)
		{
			ft_putstr_fd(strerror(errno), 1);
			write (1, "\n", 1);
			free(open);
			free(tmp);
			return (NULL);
		}
		free(open);
		if (str[i + 1] != NULL)
			pwd = ft_split(tmp, '/');
	}
	free(env_search(env, "PWD=")->content);
	env_search(env, "PWD=")->content = tmp;
	return (tmp);
}

t_env	*cd(t_env *env, char *str)
{
	char	**path;
	char	*tmp;

	if (!str)
	{
		ft_putstr_fd(env_search(env, "PWD=")->content, 1);
		(write(1, "\n", 1));
		return (env);
	}
	if (str[0] == '/')
	{
		cd_slash(env, str);
		ft_putstr_fd(env_search(env, "PWD=")->content, 1);
		(write(1, "\n", 1));
		return (env);
	}
	path = ft_split(str, '/');
	if (!path)
		error_handler(0);
	tmp = make_path(env, path);
	ft_putstr_fd(tmp, 1);
	if (tmp && tmp[0] == '/')
		(write(1, "\n", 1));
	free_tab(path);
	return (env);
}
