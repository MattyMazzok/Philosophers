# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 11:52:34 by mmazzocc          #+#    #+#              #
#    Updated: 2023/03/10 00:50:03 by mmazzocc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
FLAGS	= -Wall -Wextra -Werror -pthread

NAME	= philo

INC	= inc
SRC_PATH	= src
OBJ_PATH	= obj

SRCS = philo.c \
		utils.c \
		alloc.c \
		routine.c \
		supervisor.c \

SRC		= $(addprefix $(SRC_PATH)/,$(SRCS))
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/$(NAME).h
	@mkdir -p obj
	$(CC) $(FLAGS) -I $(INC) -c -o $@ $<

clean:
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJB_PATH)

fclean: clean
	@rm -f $(NAME) ${NAMEB}

re: fclean all


.PHONY:	all clean fclean re
