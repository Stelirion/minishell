/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:26:41 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/09 14:28:34 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_of(t_env *env)
{
	char	*str;
	if (!chdir(env_search(env, "PWD=")->content))
	{
		str = ft_strdup("/");
		if (str)
			error_handler(130, env, NULL);
		free(env_search(env, "PWD=")->content);
		env_search(env, "PWD=")->content = str;
	}
}
