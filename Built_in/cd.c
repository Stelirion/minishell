/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:48:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/05 14:59:05 by mbrement         ###   ########lyon.fr   */
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
		env_lstadd_back(&env, env_lstnew(str_tmp));
	}
	if (env_search(env, "OLDPWD=")->content)
		free (env_search(env, "OLDPWD=")->content);
	tmp = env_search(env, "OLDPWD=");
	tmp->content = strdup(env_search(env, "PWD=")->content);
	return (env);
}

t_env	*cd(t_env *env, char *str)
{
	if (!str || !ft_strlen(str))
		return (env);
	else if (chdir(str) != -1)
	{
		env = cd_old_pwd(env);
		free(env_search(env, "PWD=")->content);
		env_search(env, "PWD=")->content = get_pwd();
	}
	else
	{
		ft_putstr_fd("Minishell : cd : ", 1);
		ft_putstr_fd(strerror(errno), 1);
		write (1, "\n", 1);
		g_global.return_value = 1;
	}
	return (env);
}
