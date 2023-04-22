/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:40:44 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 19:42:20 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*shlvl(t_env *env)
{
	char	*str[2];

	if ((ft_atoi(env_search(env, "SHLVL=")->content)) > 999)
	{
		ft_putstr_fd("Minishell : warning: shell level too high", 1);
		ft_putstr_fd(" ( > 1000), resetting to 1\n", 1);
		free(env_search(env, "SHLVL=")->content);
		env_search(env, "SHLVL=")->content = ft_strdup("1");
	}
	else
	{
		str[0] = ft_itoa((ft_atoi(env_search(env, "SHLVL=")->content) + 1));
		free(env_search(env, "SHLVL=")->content);
		env_search(env, "SHLVL=")->content = str[0];
	}
	return (env);
}
