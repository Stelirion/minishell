NAME		=	minishell

LIBFT		=	libft.a

DIR_OBJS	=	./

DIR_SRCS	=	./

DIR_LIBFT	=	Tools/Libft/

HEAD	=	minishell.h

SRCS	=	main.c\
			end_of_prog.c\
			\
			Error/error.c\
			\
			Env/env_lstadd_back.c \
			Env/env_lstadd_front.c \
			Env/env_lstclear.c\
			Env/env_lstdelone.c\
			Env/env_lstlast.c\
			Env/env_lstnew.c\
			Env/env_lstsize.c\
			Env/env_search.c \
			Env/get_env.c\
			Env/env_change.c\
			Env/env_add.c\
			Env/env_clear.c\
			Env/env_unset.c\
			\
			Built_in/env.c\
			Built_in/get_pwd.c\
			Built_in/printf_export.c\
			Built_in/pwd.c\
			Built_in/cd.c\
			Built_in/echo.c\
			Built_in/case_of.c\
			Built_in/export_add.c\
			\
			Parsing/parsing.c\
			Parsing/param_lstadd_back.c\
			Parsing/param_lstclear.c\
			Parsing/param_lstnew.c\
			Parsing/readline.c\
			Parsing/param_lstsize.c\
			Parsing/type.c\
			\
			ft_split_shell.c\
			nice_thing.c\
			\
			Exec/param_to_string.c\
			Exec/exec_core.c\
			Exec/exec_child.c\
			Exec/pipe.c\
			



OBJS	=	${SRCS:%.c=${DIR_OBJS}%.o}


CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address 
#-O3 -g -pg 


RM		=	rm -rf
MKDIR	=	mkdir -p


all		:	${NAME}


${NAME}	:	${OBJS} ${addprefix ${DIR_LIBFT}, ${LIBFT}}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${DIR_LIBFT} -lft -lreadline

${addprefix ${DIR_LIBFT}, ${LIBFT}}	:
			make ${LIBFT} -C ${DIR_LIBFT}



fclean_lib		:
					make fclean -C ${DIR_LIBFT}

clean			:	fclean_lib
					${RM} ${OBJS}

fclean			:	clean fclean_lib
					${RM} ${NAME}

re				:	fclean
					${MAKE} all
normy:
				norminette $(SRCS)
				norminette $(HEAD)

# bonus			: 
# 					make -C ./Bonus
# clean_bonus		: 
# 					make clean -C ./Bonus
# fclean_bonus		: 
# 					make clean -C ./Bonus
# 					make fclean -C ./Bonus

.PHONY:	all clean fclean re fclean_lib fclean_all normy 
# bonus clean_bonus fclean_bonus