/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:45:13 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/21 23:03:42 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_piped(int arg_nb, int *pipefd, int *fd);

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
		{
			str = ft_strjoin(env_search(env, "PWD=")->content, param->content);
			if (!str)
				error_handler(130, env, param);
			s_pipe->first[0] = open(str, O_RDONLY);
			free(str);
		}
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

/*
int	pipex_core(char **argv, int arg_nb, char **envp, int *fd)
{
	int	res_fork;
	int	pipefd[2];

	pipe(pipefd);
	res_fork = fork();
	ft_piped (arg_nb, pipefd, fd);
	return (res_fork);
}

void	pipex_main(int argc, char **argv, char **envp)
{
	int	arg_nb;
	int	fd[2];
	int	res_fork;

	fd[1] = open (argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	fd[0] = open (argv[1], O_RDONLY);
	pipex_error_arg(argc, argv);
	arg_nb = 2;
	while (arg_nb <= argc - 2)
	{
	//	ft_piped (arg_nb, pipefd);
		res_fork = pipex_core(argv, arg_nb++, envp, fd);
	// close (pipefd[0]);
	//	close (file_fd_in);
		close (fd[0]);
	}
	close (fd[1]);
//	waitpid(res_fork, fd, 0);
}*/
