/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/27 15:25:23 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**env_split(char **env, int nb);
static void	env_fill(t_env *list);

t_env	*get_env(char **env)
{
	t_env	*list;
	size_t	i;


	if (!env[0])
	{
		list = env_lstnew(NULL);
		env_fill (list);
		return (list);
	}
	i = 0;
	list = env_lstnew(env_split(env, 0));
	while (env[++i])
		env_lstadd_back(&list, env_lstnew(env_split(env, i)));
	env_fill (list);
	return (list);
}

static void	env_fill(t_env *list)
{
	t_env	*tmp;
	char	*str[2];

	tmp = env_search(list, "PATH=");
	if (!tmp)
	{
		str[0] = malloc(sizeof(char) * 6);
		str[0] = "PATH=";
		str[1] = get_pwd();
		env_lstadd_back(&list, env_lstnew(str));
	}
	tmp = env_search(list, "SHLVL=");
	if (!tmp)
	{
		str[0] = malloc(sizeof(char) * 7);
		str[0] = "SHLVL=";
		str[1] = malloc(sizeof(char) * 2);
		str[1] = "1";
		env_lstadd_back(&list, env_lstnew(str));
	}
	else
	{
		tmp->content = ft_itoa(ft_atoi(tmp->content) + 1);
	}
}

char	**env_split(char **env, int nb)
{	
	size_t			i;
	char			**rtn;
	size_t			max;
	size_t			stop;

	i = 0;
	rtn = malloc(sizeof(char *) * 2);
	max = ft_strlen(env[nb]);
	if (!rtn)
		error_handler(0);
	while (i < max && env[nb][i] != '=')
		i++;
	stop = ++i;
	rtn[0] = malloc(sizeof(char) * (stop + 1));
	rtn[1] = malloc(sizeof(char) * (max - stop + 1));
	if (!rtn[0] || !rtn[1])
		error_handler(1);
	i = -1;
	while (++i < stop)
		rtn[0][i] = env[nb][i];
	rtn[0][i] = '\0';
	i = -1;
	while (++i < max - stop)
		rtn[1][i] = env[nb][stop + i];
	rtn[1][i] = '\0';
	return (rtn);
}
