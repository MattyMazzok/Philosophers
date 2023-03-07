# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmazzocc <mmazzocc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 11:52:34 by mmazzocc          #+#    #+#              #
#    Updated: 2023/03/07 11:55:50 by mmazzocc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
FLAGS	= -Wall -Wextra -Werror

NAME	= philo

INC	= inc
SRC_PATH	= src
OBJ_PATH	= obj

SRCS = philo.c \
		utils.c \
		moves.c \
		start.c \
		thread.c \

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
