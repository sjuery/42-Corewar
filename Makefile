#* ************************************************************************** */
#*                                                                            */
#*    Makefile               _             _              :::      ::::::::   */
#*    By: mlu, anazar, ihodge, sjuery     | |           :+:      :+:    :+:   */
#*     ___  __ _  __ _ _ __ | | __ _ _ __ | |_        +:+ +:+         +:+     */
#*    / _ \/ _` |/ _` | '_ \| |/ _` | '_ \| __|     +#+  +:+       +#+        */
#*   |  __/ (_| | (_| | |_) | | (_| | | | | |_    +#+#+#+#+#+   +#+           */
#*    \___|\__, |\__, | .__/|_|\__,_|_| |_|\__|        #+#    #+#             */
#*          __/ | __/ | |                             ###   ########.fr       */
#*         |___/ |___/|_|                                                     */
#* ************************************************************************** */

NAME	= corewar
ASMNAME = asm

FILES	= main parse_file
ASMFILES= assembler
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
	gcc $(CFLAGS) -L libft -lft $(IFLAGS) $^ -o $(ASMNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created ASM"

$(NAME): $(OBJ)
	make -C libft/
	gcc $(CFLAGS) -L libft -lft $(IFLAGS) $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created corewar"

./objects/%.o: ./src/%.c
	mkdir -p objects
	gcc $(IFLAGS) -c $< -o $@

clean:
	make fclean -C libft/
	/bin/rm -f *.o
	/bin/rm -rf ./objects/*.o
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned corewar"

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)
	/bin/rm -f $(ASMNAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned corewar"

re: fclean all

.PHONY: clean fclean re all test