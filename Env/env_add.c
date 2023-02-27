/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:11:43 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 16:33:04 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_add(t_env *env, char *str)
{
	char	*tmp[1];
	char	**add;
	t_env	*tmp_env;

	tmp[0] = str;
	add = env_split(tmp, 0);
	tmp_env = env_search_less(env, add[0]);
	if (tmp_env)
	{
		free(tmp_env->content);
		tmp_env->content = add[1];
	}
	else
	{
		env_lstadd_back(&env, env_lstnew(add));
	}
	free(add[0]);
	free(add);
}
