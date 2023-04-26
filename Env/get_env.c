/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:07:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 13:54:16 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**env_split(char **env, int nb);
char		**env_split2(char **env, int nb, size_t *i, char **rtn);
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
		if (!list)
			error_handler(130, NULL, NULL);
		return (env_fill (list), tmp = list->next, free(list), tmp);
	}
	i = 0;
	str = env_split(env, 0);
	list = env_lstnew(str);
	if (!list)
		error_handler(130, NULL, NULL);
	free(str);
	while (env[++i])
	{
		str = env_split(env, i);
		env_lstadd_back(&list, env_lstnew(str));
		free(str);
	}
	return (env_fill (list), list);
}

t_env	*fill_in(int nb, t_env *env)
{
	char	*str[2];

	if (nb == 1)
	{
		str[0] = ft_strdup("PWD=");
		str[1] = get_pwd(NULL);
		env_lstadd_back(&env, env_lstnew(str));
	}
	else if (nb == 2)
	{
		str[0] = ft_strdup("SHLVL=");
		str[1] = ft_strdup("1");
		env_lstadd_back(&env, env_lstnew(str));
	}
	else if (nb == 3)
		env = shlvl(env);
	else if (nb == 4)
	{
		str[0] = ft_strdup("OLDPWD=");
		str[1] = ft_strdup("/");
		env_lstadd_back(&env, env_lstnew(str));
	}
	return (env);
}

static void	env_fill(t_env *list)
{
	t_env	*tmp;

	tmp = env_search(list, "PWD=");
	if (!tmp)
		list = fill_in(1, list);
	tmp = env_search(list, "SHLVL=");
	if (!tmp)
		list = fill_in(2, list);
	else
		list = fill_in(3, list);
	tmp = env_search(list, "OLDPWD=");
	if (!tmp)
		list = fill_in(4, list);
	tmp = list;
	while (tmp)
	{
		if (tmp->content && tmp->content[0] != '\0')
			tmp->is_env = 1;
		tmp->is_export = 1;
		tmp = tmp->next;
	}
}

char	**env_split(char **env, int nb)
{	
	size_t			i[3];
	char			**rtn;

	i[0] = 0;
	rtn = malloc(sizeof(char *) * 2);
	if (!rtn)
		error_handler(130, NULL, NULL);
	i[1] = ft_strlen(env[nb]);
	while (i[0] < i[1] && env[nb][i[0]] != '=')
		i[0]++;
	if (env[nb][i[0]] == '=')
		i[2] = ++i[0];
	else
		i[2] = i[0];
	rtn[0] = malloc(sizeof(char) * (i[2] + 1));
	rtn[1] = malloc(sizeof(char) * (i[1] - i[2] + 1));
	if (!rtn[0] || !rtn[1])
		error_handler(130, NULL, NULL);
	rtn = env_split2(env, nb, i, rtn);
	return (rtn);
}

char	**env_split2(char **env, int nb, size_t *i, char **rtn)
{
	char	*tmp;

	i[0] = -1;
	while (++i[0] < i[2])
		rtn[0][i[0]] = env[nb][i[0]];
	rtn[0][i[0]] = '\0';
	if (rtn[0][i[0] - 1] != '=')
	{
		tmp = ft_strjoin(rtn[0], "=");
		free(rtn[0]);
		rtn[0] = tmp;
	}
	i[0] = -1;
	while (++i[0] < i[1] - i[2])
		rtn[1][i[0]] = env[nb][i[2] + i[0]];
	rtn[1][i[0]] = '\0';
	return (rtn);
}
