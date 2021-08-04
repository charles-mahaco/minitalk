# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charles <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 19:05:17 by charles           #+#    #+#              #
#    Updated: 2021/07/31 17:22:22 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= server
CLIENT				= client
BONUS				= bonus_comp
CC					= gcc
RM					= rm -rf

CFLAGS				= -Wall -Wextra -Werror
IFLAGS				= -I${INC_DIR}

SRCS_DIR			= utils
INC_DIR				= includes
OBJS_DIR			= objs

INC				 	= $(shell find ${INC_DIR} -type f -name "*.h")
SRCS 				= $(notdir $(shell find ${SRCS_DIR} -type f -name "*.c"))
OBJS 				= $(addprefix ${OBJS_DIR}/, ${SRCS:.c=.o})
vpath				%.c $(shell find ${SRCS_DIR} -type d)
				
all: 				init ${NAME}

init:
					$(shell mkdir -p ${OBJS_DIR})

${NAME}:			${OBJS}
					@${CC} ${CFLAGS} ${IFLAGS} client.c -o ${CLIENT} $^
					@${CC} ${CFLAGS} ${IFLAGS} server.c -o $@ $^
					@echo "Done"

bonus:				init ${BONUS}

${BONUS}:			${OBJS}
					@${CC} ${CFLAGS} ${IFLAGS} client_bonus.c -o ${CLIENT} $^
					@${CC} ${CFLAGS} ${IFLAGS} server_bonus.c -o ${NAME} $^
					@echo "Done"
					
${OBJS_DIR}/%.o:	%.c
					@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@
	
clean:
					@${RM} ${OBJS_DIR}

fclean:				clean
					@${RM} ${NAME}
					@${RM} ${CLIENT}

re:					fclean all

.SUFFIXES:			.c .o .h
.PHONY:				all clean fclean re

