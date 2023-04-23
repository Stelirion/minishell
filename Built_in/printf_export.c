/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:59:48 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/23 03:34:59 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	find_target(t_env *env, t_env *target, size_t nb, size_t test);

t_env	*find_next(t_env *list, size_t nb)
{
	t_env	*target;
	t_env	*tmp;
	size_t	test;

	target = list;
	tmp = list->next;
	test = 0;
	while (1)
	{
		test = find_target(tmp, target, nb, test);
		if (test == nb)
			return (target);
		target = target->next;
		if (!target || (target && !target->next))
			break ;
		tmp = list;
		test = 0;
	}
	return (target);
}

static size_t	find_target(t_env *env, t_env *target, size_t nb, size_t test)
{
	size_t	i;

	while (env)
	{
		i = 0;
		while (env->name[i] && target->name[i]
			&& target->name[i] == env->name[i])
			i++;
		if (target->name[i] > env->name[i]
			|| (!env->name[i] && target->name[i]))
			test++;
		if (nb < test)
			break ;
		env = env->next;
	}
	return (test);
}

void	print_export(t_env *list)
{
	size_t	i;
	t_env	*target;

	i = 0;
	target = find_next(list, i);
	while (i < env_lstsize(list))
	{
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(target->name, 1);
		ft_putstr_fd(target->content, 1);
		write (1, "\n", 1);
		i++;
		target = find_next(list, i);
	}
	g_return_value = 0;
}
