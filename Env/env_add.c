/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:11:43 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/20 03:30:14 by mbrement         ###   ########lyon.fr   */
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

static void	export_error(char **add)
{
	add[0][ft_strlen(add[0]) - 1] = '\0';
	ft_putstr_fd("Minishell : export: `", 2);
	ft_putstr_fd(add[0], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(add[0]);
	free(add[1]);
	free(add);
	g_return_value = 1;
}

void	env_add(t_env *env, char *str)
{
	char	*tmp[1];
	char	**add;
	t_env	*tmp_env;
	size_t	i;

	i = 0;
	if (!str || !*str)
		return ;
	tmp[0] = str;
	add = env_split(tmp, 0);
	tmp_env = env_search(env, add[0]);
	while (add[0][i])
	{
		if (ft_isalpha(add[0][i]) || add[0][i] == '_'
			|| (i != 0 && ft_isalpha(add[0][i])))
			i++;
		else if (add[0][i] == '=' && i > 0)
			i++;
		else
			return (export_error(add));
	}
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
	g_return_value = 0;
}
