/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:36:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/04 13:48:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Tools/Libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <string.h>

# include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	int				is_env;
	int				is_export;
	struct s_env	*next;
}					t_env;

int	g_return_value;

void	end_of_prog(t_env *env, int i);

///ENV
void	env_lstadd_back(t_env **lst, t_env *next);
void	env_lstadd_front(t_env **lst, t_env *next);
void	env_lstclear(t_env **lst);
void	env_lstdelone(t_env *lst);
t_env	*env_lstlast(t_env *lst);
t_env	*env_lstnew(char **content);
size_t	env_lstsize(t_env *lst);
t_env	*env_search(t_env *list, char *str);
t_env	*get_env(char **env);
void	env_change(char *name, char *content, t_env *env);
char	**env_split(char **env, int nb);
void	env_add(t_env *env, char *str);
void	env_clear(t_env *env);
t_env	*env_search_before(t_env *list, char *str);
t_env	*env_unset(t_env *env, char *str);
void	print_export(t_env *list);



///BUILT_IN
void	pwd(t_env *env);
void	print_env(t_env *list);
char	*get_pwd(void);
t_env	*cd(t_env *env, char *str);
void	echo(char	**str);

///ERROR
void	error_handler(int name);

//TEMPORARY
char	**ft_split_shell(char const *s);

#endif