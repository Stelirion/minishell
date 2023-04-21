/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:48:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/21 19:59:18 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*cd_old_pwd(t_env	*env)
{
	t_env	*tmp;
	char	*str_tmp[1];

	if (!env_search(env, "OLDPWD="))
	{
		str_tmp[0] = "OLDPWD";
		tmp = env_lstnew(str_tmp);
		if (!tmp)
			error_handler(130, env, NULL);
		env_lstadd_back(&env, tmp);
	}
	if (env_search(env, "OLDPWD=")->content)
		free (env_search(env, "OLDPWD=")->content);
	tmp = env_search(env, "OLDPWD=");
	tmp->content = ft_strdup(env_search(env, "PWD=")->content);
	return (env);
}

t_env	*cd(t_env *env, char *str)
{
	if (!str)
		return (env);
	if (ft_strlen(str) == 0)
	{
		free(env_search(env, "PWD=")->content);
		env_search(env, "PWD=")->content = ft_strdup("/");
	}
	else if (chdir(str) != -1)
	{
		env = cd_old_pwd(env);
		free(env_search(env, "PWD=")->content);
		env_search(env, "PWD=")->content = get_pwd(env);
	}
	else
	{
		ft_putstr_fd("Minishell : cd : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write (1, "\n", 2);
		g_return_value = 1;
	}
	return (env);
}
