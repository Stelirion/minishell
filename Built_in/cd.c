/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:48:20 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 16:48:27 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*cd_old_pwd(t_env	*env)
{
	t_env	*tmp;
	char	**str_tmp;

	if (!env_search(env, "OLDPWD="))
	{
		str_tmp = ft_split("OLDPWD= /", ' ');
		tmp = env_lstnew(str_tmp);
		if (!tmp)
			error_handler(130, env, NULL);
		env_lstadd_back(&env, tmp);
	}
	if (env_search(env, "OLDPWD=") && env_search(env, "OLDPWD=")->content)
	{
		tmp = env_search(env, "OLDPWD=");
		free (tmp->content);
		if (env_search(env, "PWD=") && env_search(env, "PWD=")->content
			&& tmp)
			tmp->content = ft_strdup(env_search(env, "PWD=")->content);
	}
	return (env);
}

static void	print_cd(void)
{
	ft_putstr_fd("Minishell : cd : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write (1, "\n", 2);
	g_return_value = 1;
}

t_env	*cd(t_env *env, char *str)
{
	char	*tmp[2];

	if (!str)
		return (env);
	if (env_search(env, "PWD=") == 0)
	{	
		tmp[0] = ft_strdup("PWD=");
		tmp[1] = ft_strdup(" ");
		env_lstadd_back(&env, env_lstnew(tmp));
	}
	if (ft_strlen(str) == 0)
	{
		free(env_search(env, "PWD=")->content);
		env_search(env, "PWD=")->content = ft_strdup("/");
	}
	else if (chdir(str) != -1)
	{
		env = cd_old_pwd(env);
		if (env_search(env, "PWD=")->content)
			free(env_search(env, "PWD=")->content);
		env_search(env, "PWD=")->content = get_pwd(env);
	}
	else
		print_cd();
	return (env);
}
