/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:36:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/07 21:02:07 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Tools/Libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	int				is_env;
	int				is_export;
	struct s_env	*next;
}					t_env;


typedef struct s_param
{
	char			*content;
	int				type;
	struct s_param	*next;
}					t_param;

typedef struct s_global
{
	int		return_value;
	t_env	*env;
	t_param	*param;
}					t_global;

t_global	g_global;

void	end_of_prog(t_env *env, int i);
void	end_of_prog_exit(t_global g_global, int i);


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
t_env	*env_unset(t_env *env, char *str);

///EXEC
void	exec_core(t_param	*param, t_env *env);
char	**param_to_array(t_param *param);

///BUILT_IN
void	pwd(void);
void	print_env(t_env *list);
char	*get_pwd(void);
t_env	*cd(t_env *env, char *str);
void	echo(char	**str);
void	case_of(t_env *env);
void	export_handler(t_param *param, t_env *env);

///ERROR
void	error_handler(int name);

///PARSING
t_param	*parsing_core(char *line, t_param *param);
void	param_lstadd_back(t_param **lst, t_param *next);
t_param	*param_lstnew(char *content);
void	param_lstclear(t_param **lst);
size_t	param_lstsize(t_param *lst);



//TEMPORARY
char	**ft_split_shell(char const *s);

#endif