/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:52:02 by ngennaro          #+#    #+#             */
/*   Updated: 2023/05/01 18:55:13 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_heredoc_env(t_env *new)
{
	static t_env	*env;

	if (new)
		env = new;
	return (env);
}

t_param	*get_heredoc_param(t_param *new)
{
	static t_param	*env;

	if (new)
		env = new;
	return (env);
}

void	signal_heredoc(int tmp)
{
	t_env	*env;
	t_param	*param;

	(void)tmp;
	env = get_heredoc_env(NULL);
	param = get_heredoc_param(NULL);
	g_return_value = -1;
	end_of_prog_exit(env, param, 0);
}

int	heredoc_child(t_param *param, t_env *env, int fd, char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, signal_heredoc);
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("heredoc exit\n", 1);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	return (end_of_prog_exit(env, param, 0), 0);
}

int	heredoc(char *limiter, t_param *param, t_env *env)
{
	int		res_fork;
	int		fd;
	int		status;

	fd = open("/var/tmp/minishell.tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	get_heredoc_param(param);
	get_heredoc_env(env);
	res_fork = fork();
	if (res_fork == 0)
		return (heredoc_child(param, env, fd, limiter));
	else
	{
		waitpid(res_fork, &status, 0);
		if (WEXITSTATUS(status) == 255)
			return (-1);
		close(fd);
		return (fd);
	}
}
