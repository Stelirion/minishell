/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:40:53 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/20 15:17:10 by ngennaro         ###   ########.fr       */
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

void	inception(char *token)
{
	size_t	i;
	int		check;
	char	*to_check;

	i = 0;
	check = 0;
	to_check = "llehsinim/";
	while (token[i])
		i++;
	while (to_check[check])
	{
		i--;
		if (to_check[check] != token[i])
			return ;
		check++;
	}
	signal(SIGINT, SIG_IGN);
}
