/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:11:43 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/28 13:41:42 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static	int	find_equal(char *str)
{
	while (*str != '\0')
	{
		if (*str == '=')
			return (1);
		else
			str++;
	}
	return (0);
}

void	env_add(t_env *env, char *str)
{
	char	*tmp[1];
	char	**add;
	t_env	*tmp_env;

	if (!str || !*str)
		return ;
	tmp[0] = str;
	add = env_split(tmp, 0);
	tmp_env = env_search(env, add[0]);
	if (tmp_env)
	{
		free(tmp_env->content);
		tmp_env->content = add[1];
		free(add[0]);
	}
	else
	{
		env_lstadd_back(&env, env_lstnew(add));
		if (find_equal(str))
			env_lstlast(env)->is_env = 1;
		else
			env_lstlast(env)->is_env = 0;
		env_lstlast(env)->is_export = 1;
	}
	free(add);
}
