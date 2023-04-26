/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:40:53 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/26 17:40:15 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(int tmp)
{
	(void)tmp;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	cancel_commande(int tmp)
{
	(void)tmp;
	ft_putstr_fd("\n", 1);
	return ;
}

void	command_back(int tmp)
{
	(void)tmp;
	ft_putstr_fd("Quit\n", 1);
	return ;
}

void	inception(char *token)
{
	size_t	i;
	char	*to_check;

	i = 0;
	to_check = "/minishell";
	while (token[i])
		i++;
	if (i > 10)
	{
		i -= 10;
		if (ft_strcmp(token + i, to_check))
			return ;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, cancel_commande);
		signal(SIGQUIT, command_back);
	}
}
