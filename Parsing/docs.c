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

int heredoc(char *limiter)
{
	char	*line;
	int		fd[2];

	line = NULL;
    fd[1] =  open("/var/tmp/minishell.tmp", O_CREAT | O_WRONLY, 0644);
	while (1)
	{
		line = readline("> ");
        if (!line)
        {
            ft_putstr_fd ("heredoc exit\n", 1);
            break;
        }
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd[1]);
        ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
    return(fd[1]);
}

t_param *manage_dock(t_param *param)
{
	t_param	*init;

	init = param;
	while (param)
	{
        if (param->type == HEREDOC)
            param->heredoc_fd = heredoc(param->content);
        param = param->next;
    }
    return(init);
}