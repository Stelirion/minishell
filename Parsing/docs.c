/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   docs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:50:36 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/19 23:02:25 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_param	*manage_dock(t_param *param, t_env *env)
{
	t_param		*init;

	init = param;
	while (param)
	{
		if (param->type == HEREDOC)
		{
			param->heredoc_fd = heredoc(param->content, init, env);
			if (param->heredoc_fd == -1)
				return (param_lstclear(&init), NULL);
		}
		param = param->next;
	}
	return (init);
}
