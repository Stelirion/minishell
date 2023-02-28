/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/28 13:27:57 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**env_split(char **env, int nb);
static void	env_fill(t_env *list);

t_env	*get_env(char **env)
{
	t_env	*list;
	t_env	*tmp;
	size_t	i;
	char	**str;


	if (!env[0])
	{
		list = env_lstnew(NULL);
		env_fill (list);
		tmp = list->next;
		free(list);
		return (tmp);
	}
	i = 0;
	str = env_split(env, 0);
	list = env_lstnew(str);
	free(str);
	while (env[++i])
	{
		str = env_split(env, i);
		env_lstadd_back(&list, env_lstnew(str));
		free(str);
	}
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
		str[0] = ft_strdup("PATH=");
		str[1] = get_pwd();
		env_lstadd_back(&list, env_lstnew(str));
	}
	tmp = env_search(list, "SHLVL=");
	if (!tmp)
	{
		str[0] = ft_strdup("SHLVL=");
		str[1] = ft_strdup("1");
		env_lstadd_back(&list, env_lstnew(str));
	}
	else
	{
		free(tmp->content);
		tmp->content = ft_itoa(ft_atoi(tmp->content) + 1);
	}
	tmp = list;
	while (tmp)
	{
		tmp->is_env = 1;
		tmp->is_export = 1;
		tmp = tmp->next;
	}
}

char	**env_split(char **env, int nb)
{	
	size_t			i;
	char			**rtn;
	size_t			max;
	size_t			stop;
	char 			*tmp;

	i = 0;
	rtn = malloc(sizeof(char *) * 2);
	if (!rtn)
		error_handler(0);
	max = ft_strlen(env[nb]);
	while (i < max && env[nb][i] != '=')
		i++;
	if (env[nb][i] == '=')
		stop = ++i;
	else
		stop = i;
	rtn[0] = malloc(sizeof(char) * (stop + 1));
	rtn[1] = malloc(sizeof(char) * (max - stop + 1));
	if (!rtn[0] || !rtn[1])
		error_handler(1);
	i = -1;
	while (++i < stop)
		rtn[0][i] = env[nb][i];
	rtn[0][i] = '\0';
	if (rtn[0][i - 1] != '=')
	{
		tmp = ft_strjoin(rtn[0], "=");
		free(rtn[0]);
		rtn[0] = tmp;
	}
	i = -1;
	while (++i < max - stop)
		rtn[1][i] = env[nb][stop + i];
	rtn[1][i] = '\0';
	return (rtn);
}
