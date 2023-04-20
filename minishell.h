/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:36:01 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/20 15:11:31 by mbrement         ###   ########lyon.fr   */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	int				is_env;
	int				is_export;
	struct s_env	*next;
}					t_env;

# define CMD 1

# define INFILE 2

# define OUTFILE 3

# define ARG 4

# define PIPE 5

# define APPEND 6

# define HEREDOC 7

typedef struct s_param
{
	char			*content;
	int				type;
	int				heredoc_fd;
	struct s_param	*next;
}					t_param;

typedef struct s_pipe
{
	int	first[2];
	int	second[2];
	int	counter;
}					t_pipe;

typedef struct s_pid
{
	int				*pid;
	struct s_pid	*next;
}					t_pid;

extern int	g_return_value;

void	header(void);
void	new_prompt(int tmp);
void	cancel_commande(int tmp);
void	end_of_prog(t_env *env, int i);
void	end_of_prog_exit(t_env *env, t_param *param, int i);
void	end_of_prog_exit_fd(t_env *env, t_param *param, int i, int *fd);

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
void	exec_core(t_param	*param, t_env *env, int *fd_org);
char	**param_to_array(t_env *env, t_param *param);
char	**param_to_arg(t_env *env, t_param *param);
char	**env_to_array(t_env *env, t_param *param);
int		try_exec(t_env *env, t_param *param);
int		*first_pipe(t_env *env, t_param *param);
t_pipe	*ft_pipe(t_param *param, t_env *env, t_pipe *pipe);
int		exec_pipe(t_env *env, t_param *param, t_pipe spipe, t_pid	*pid);
int		exec_pure(t_env *env, t_param *param, int *fd_org, t_pid *pid);
int		is_built_in(t_param	*param, t_env *env, int *fd, t_pid *pid);
int		ft_redirect(t_param *param, int *i);
void	ft_undup(int *i);
void	handle_pipe(t_env *env, t_param *param, int *fd_org, t_pid	*pid);
t_pid	*pid_lstnew(int pid);
void	pid_lstadd_back(t_pid **pid, t_pid *next);
void	pid_clear(t_pid *pid);
void	waiting(t_pid *pid);
int		exec_pure_p(t_env *env, t_param *param, int *fd_org, t_pid *pid);

///BUILT_IN
void	pwd(void);
void	print_env(t_env *list);
char	*get_pwd(void);
t_env	*cd(t_env *env, char *str);
void	echo(char	**str);
void	case_of(t_env *env);
void	export_handler(t_param *param, t_env *env);

///ERROR
void	error_handler(int name, t_env *env, t_param *param);

///PARSING
t_param	*parsing_core(char *line, t_param *param, t_env *env);
void	param_lstadd_back(t_param **lst, t_param *next);
t_param	*param_lstnew(char *content);
void	param_lstclear(t_param **lst);
size_t	param_lstsize(t_param *lst);
t_param	*type_setting(t_param *param);
size_t	param_lstsize_nb_arg(t_param *lst);
void	parsing_error(int type);
t_param	*manage_dock(t_param *param, t_env *env);

//TEMPORARY
char	**ft_split_shell(char const *s);
char	*last_str(t_env *env);

#endif