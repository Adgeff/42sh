# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 17:11:19 by geargenc          #+#    #+#              #
#    Updated: 2019/02/03 12:57:50 by geargenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT			:

NAME			=	42sh

CC				= 	gcc

CFLAGS			=	-Wall -Wextra -Werror -I includes

FILES			=	ft_lexer.c\
					main.c

SRC_DIR			=	src/

SRC				=	$(addprefix $(SRC_DIR), $(FILES))

OBJ_DIR			=	obj/

OBJ				=	$(addprefix $(OBJ_DIR), $(FILES:.c=.o))

DEP_DIR			=	dep/

DEP				=	$(addprefix $(DEP_DIR), $(FILES:.c=.d))

all				:	$(NAME)

$(DEP_DIR)%.d	:	$(SRC_DIR)%.c
	@mkdir -p $(DEP_DIR)
	@$(CC) $(CFLAGS) -MM $< -MT $(OBJ_DIR)$*.o -MF $@
	@printf "\r\E[K\033[1;33mCreated : $@\033[0m"

-include $(DEP)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\E[K\033[1;33mCreated : $@\033[0m"

$(NAME)			:	$(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $@
	@printf "\r\E[K\033[1;32mCreated : $@\033[0m\n"

clean			:
	@rm -rf obj
	@printf "\033[1;31mRemoved : $(OBJ_DIR)\033[0m\n"
	@rm -rf dep
	@printf "\033[1;31mRemoved : $(DEP_DIR)\033[0m\n"

fclean			:	clean
	@make fclean -C libft
	@rm -f $(NAME)
	@printf "\033[1;31mRemoved : $(NAME)\033[0m\n"

re				:
	@$(MAKE) $(MFLAGS) fclean
	@$(MAKE) $(MFLAGS) all

.PHONY			:	all clean fclean re
