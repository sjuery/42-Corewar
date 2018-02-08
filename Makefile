# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by _| |_|\__|        #+#    #+#              #
#    Updated: 2018/02/07 20:11:33 by sjuery           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= corewar
ASMNAME = asm

FILES	= main parse_file
ASMFILES= assembler convert_to_hex
ASMSRC	= $(patsubst %, %.c, $(ASMFILES))
ASMOBJ 	= $(addprefix ./objects/, $(ASMSRC:.c=.o))
SRC		= $(patsubst %, %.c, $(FILES))
OBJ 	= $(addprefix ./objects/, $(SRC:.c=.o))
CFLAGS	= -Wall -Wextra -Werror -g
IFLAGS	= -I libft/includes -I includes

.SILENT:

all: $(ASMNAME) $(NAME)

$(ASMNAME): $(ASMOBJ)
	make -C libft/
	gcc $(CFLAGS) -L libft -lft -lncurses $(IFLAGS) $^ -o $(ASMNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created ASM"

$(NAME): $(OBJ)
	make -C libft/
	gcc $(CFLAGS) -L libft -lft $(IFLAGS) $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created Corewar"

./objects/%.o: ./src/%.c
	mkdir -p objects
	gcc $(IFLAGS) -c $< -o $@

clean:
	make fclean -C libft/
	/bin/rm -f *.o
	/bin/rm -rf ./objects/*.o
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned Corewar & ASM"

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)
	/bin/rm -f $(ASMNAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned Corewar & ASM"

re: fclean all

.PHONY: clean fclean re all test
