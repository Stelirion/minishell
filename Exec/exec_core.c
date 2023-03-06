/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/06 13:19:33 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

int	is_built_in(t_param	*param, t_env *env)
{
	char	**str;

	if (!ft_strncmp(param->content, "exit", 4)) //MUST CHANGE TO FT_STRCMP
		end_of_prog_exit(g_global, 0);
	else if (!ft_strncmp(param->content, "echo", 4)) //MUST CHANGE TO FT_STRCMP
	{
		str = param_to_array(param->next);
		echo(str);
		free_tab(str);
		return (g_global.return_value);
	}
	else if (!ft_strncmp(param->content, "cd", 2)) //MUST CHANGE TO FT_STRCMP
	{
		if (param_lstsize(param) > 2)
			ft_putstr_fd("Minishell : cd took only 1 argument\n", 1);
		else
		{
			if (param->next && param->next->content)
				cd(env, param->next->content);
			else 
				cd(env, "");
		}
		return (g_global.return_value);
	}
	else if (!ft_strncmp(param->content, "env", 3)) //MUST CHANGE TO FT_STRCMP)
	{
		print_env(env);
	}
	else if (!ft_strncmp(param->content, "pwd", 3)) //MUST CHANGE TO FT_STRCMP)
		pwd();
	else if (!ft_strncmp(param->content, "export", 6)) //MUST CHANGE TO FT_STRCMP)
		export_handler(param, env);
	else if (!ft_strncmp(param->content, "unset", 5))
		env = env_unset(env, param->content);
	else
		return (1);
	return (g_global.return_value);
}

void	exec_core(t_param	*param, t_env *env)
{
	if (param && param->content)
		printf("trying to do |%s|\n", param->content);
	if (param && !is_built_in(param, env))
		return ;
	else
		ft_putstr_fd("not implemented yet,but soon ;-)\n", 1);
}
