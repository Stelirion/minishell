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
	printf("pouet");
	end_of_prog_exit(env, param, -1);
}

int	heredoc(char *limiter, t_param *param, t_env *env)
{
	int		res_fork;
	char	*line;
	int		fd[2];

	line = NULL;
	fd[1] = open("/var/tmp/minishell.tmp", O_CREAT | O_WRONLY, 0644);
	get_heredoc_param(param);
	get_heredoc_env(env);
	res_fork = fork();
	if (res_fork == 0)
	{
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
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			free(line);
		}
		close(fd[1]);
		return (end_of_prog_exit(env, param, 0), 0);
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		close(fd[1]);
		printf("%d", g_return_value);
		if (g_return_value == -1)
			return (-1);
		return (fd[1]);
	}
}

t_param	*manage_dock(t_param *param, t_env *env)
{
	t_param		*init;

	init = param;
	while (param)
	{
		if (param->type == HEREDOC)
		{
			param->heredoc_fd = heredoc(param->content, param, env);
			if (param->heredoc_fd == -1)
				return (param_lstclear(&init), NULL);
		}
		param = param->next;
	}
	return (init);
}
