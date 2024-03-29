# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 07:36:16 by tmaillar          #+#    #+#              #
#    Updated: 2024/03/26 15:55:51 by tmaillar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= philo

CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -pthread
CFLAGS		+= -I./include
CPPFLAGS	+= -MMD -MP -MF $(@:.o=.d)

SRC_DIR		:= ./src
OBJ_DIR		:= ./obj

UTILS_SRC	:= \
	utils.c
UTILS_DIR	:= $(addprefix $(SRC_DIR)/, utils)
UTILS_OBJ	:= $(addprefix $(OBJ_DIR)/utils/, $(UTILS_SRC:.c=.o))

ROOT_SRC	:= \
	main.c \
	philo.c \
	thread.c \
	error.c \
	check.c \
	time.c \
	init_mutex.c \
	init_all.c \
	monitor.c
ROOT_DIR	:= $(SRC_DIR)
ROOT_OBJ	:= $(addprefix $(OBJ_DIR)/, $(ROOT_SRC:.c=.o))

SRC			:= \
	$(UTILS_SRC) \
	$(GC_SRC) \
	$(ROOT_SRC) 

OBJ			:= \
	$(UTILS_OBJ) \
	$(GC_OBJ) \
	$(ROOT_OBJ) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

release: CFLAGS += -02

DEBUG	:=0

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

.PHONY : all clean debug fclean re release

-include $(OBJ:.o=.d)