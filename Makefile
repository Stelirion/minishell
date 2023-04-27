NAME		=	minishell

LIBFT		=	libft.a

DIR_OBJS	=	./

DIR_SRCS	=	./

DIR_LIBFT	=	Libft/

HEAD	=	minishell.h

SRCS	=	main.c\
			end_of_prog.c\
			signal.c\
			misc.c\
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
			Env/shlvl.c\
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
			Parsing/param_lstsize.c\
			Parsing/type.c\
			Parsing/parsing_error.c\
			Parsing/docs.c\
			Parsing/heredoc.c\
			Parsing/parsing_core.c\
			Parsing/type_handler.c\
			\
			Exec/param_to_string.c\
			Exec/exec_core.c\
			Exec/exec_child.c\
			Exec/pipe.c\
			Exec/exec_pure.c\
			Exec/exec_pipe.c\
			Exec/redirect.c\
			Exec/s_pid.c\
			Exec/exec_child2.c\
			Exec/exec_order.c\

OBJS	=	${SRCS:%.c=${DIR_OBJS}%.o}

DEPS = ${SRCS:%.c=${DIR_OBJS}%.d}

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -lreadline -MMD -MP -g3 #-fsanitize=address 
#-O3 -g -pg 


RM		=	rm -rf
MKDIR	=	mkdir -p


all		:	${NAME}

DEP_FLAGS		=	-MMD -MP

-include $(DEPS)

${NAME}	:	${OBJS} ${addprefix ${DIR_LIBFT}, ${LIBFT}}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${DIR_LIBFT} -lft -lreadline

${addprefix ${DIR_LIBFT}, ${LIBFT}}	:
			make ${LIBFT} -C ${DIR_LIBFT}

fclean_lib		:
					make fclean -C ${DIR_LIBFT}

clean			:	fclean_lib
					${RM} ${OBJS}
					${RM} ${DEPS}

fclean			:	clean fclean_lib
					${RM} ${NAME}

re				:	fclean
					${MAKE} all
normy:
				norminette $(SRCS) | grep Error:
				norminette $(HEAD) | grep Error:

# bonus			: 
# 					make -C ./Bonus
# clean_bonus		: 
# 					make clean -C ./Bonus
# fclean_bonus		: 
# 					make clean -C ./Bonus
# 					make fclean -C ./Bonus

.PHONY:	all clean fclean re fclean_lib fclean_all normy 
# bonus clean_bonus fclean_bonus