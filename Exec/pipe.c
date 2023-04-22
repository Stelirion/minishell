/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:45:13 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 18:51:47 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_piped(int arg_nb, int *pipefd, int *fd);
static	void	ft_infile(t_param *param, t_env *env, t_pipe *s_pipe);

int	*first_pipe(t_env *env, t_param *param)
{
	int		*tab;
	int		fd[0];
	char	*str;
	t_param	*tmp;

	tmp = param;
	while (tmp)
	{
		if (tmp->type == INFILE)
			break ;
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
	}
	tab = malloc(sizeof(int *) * 2);
	str = ft_strjoin(env_search(env, "PWD")->content, tmp->content);
	fd[0] = open(str, O_RDONLY);
	if (fd[0])
		return (ft_putstr_fd(strerror(errno), 2), NULL);
	if (pipe(tab) == -1)
		error_handler(131, env, param);
	fd[1] = 0;
	ft_piped (1, tab, fd);
	return (tab);
}

void	ft_piped(int arg_nb, int *pipefd, int *fd)
{
	if (arg_nb == 0)
	{
		dup2(fd[0], 0);
		dup2(pipefd[1], 1);
		close(fd[0]);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	else
	{
		dup2(pipefd[0], 0);
		dup2(fd[1], 1);
		close(fd[1]);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

t_pipe	*ft_pipe(t_param *param, t_env *env, t_pipe *s_pipe)
{
	char	*str;
	t_param	*tmp;

	tmp = param;
	s_pipe->second[0] = 0;
	s_pipe->second[1] = 1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE)
			ft_infile(param, env, s_pipe);
		if (tmp->type == OUTFILE)
		{
			str = ft_strjoin(env_search(env, "PWD=")->content, param->content);
			if (!str)
				error_handler(130, env, param);
			s_pipe->first[1] = open (str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			free(str);
		}
		tmp = tmp->next;
	}
	ft_piped(s_pipe->counter, s_pipe->second, s_pipe->first);
	return (s_pipe);
}

static	void	ft_infile(t_param *param, t_env *env, t_pipe *s_pipe)
{
	char	*str;

	str = ft_strjoin(env_search(env, "PWD=")->content, param->content);
	if (!str)
		error_handler(130, env, param);
	s_pipe->first[0] = open(str, O_RDONLY);
	free(str);
}
