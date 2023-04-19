/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   docs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:50:36 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/19 20:19:46 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int heredoc(char *limiter)
{
	char	*line;
	char	*tmp;
	int		fd[2];

	line = NULL;
	tmp = "heredoc> ";
	if (pipe(fd) == -1)
		exit(1);
	while (1)
	{
		line = readline(tmp);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	//manage the infile here
    free(limiter);
	close(fd[1]);
    return(fd[1]);
}

t_param *manage_dock(t_param *param)
{
	t_param	*init;
    char    *limiter;

	init = param;
	while (param)
	{
        if (param->type == 6 || param->type == 7)
        {
            limiter = param->content;
            param->content = ft_itoa(heredoc(limiter));
        }
        param = param->next;
    }
    return(init);
}