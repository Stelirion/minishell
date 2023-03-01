/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:19:56 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/01 02:00:46 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main (int argc, char **argv)
{
    size_t  i;
    size_t  len;
    char    *line;
    char *new_str;
    t_param *param;
    t_param *new_lst;
    
    printf (" ____    ____   _             _          __             __   __   \n");
    printf ("|_   \\  /   _| (_)           (_)        [  |           [  | [  |  \n");
    printf ("  |   \\/   |   __   _ .--.   __   .--.   | |--.  .---.  | |  | |  \n");
    printf ("  | |\\  /| |  [  | [ `.-. | [  | ( (`\\]  | .-. |/ /__\\  | |  | |  \n");
    printf (" _| |_\\/_| |_  | |  | | | |  | |  `'.'.  | | | || \\__., | |  | |  \n");
    printf ("|_____||_____|[___][___||__][___][\\__) )[___]|__]'.__.'[___][___] \n");

              
    line = readline("Enter a line: ");
    printf("%s\n", line);
    i = 0;
    while (line[i])
    {
        len = 0;
        while (line[i] && line[i] != ' ')
            len++;
        new_str = ft_substr(line, i-len, len);
        new_lst = param_lstnew(new_str);
        param_lstadd_back(param, new_lst);
        i++;
    }
}