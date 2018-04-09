#* ************************************************************************** */
#*                                                                            */
#*    Makefile               _             _              :::      ::::::::   */
#*    By: mlu, anazar, ihodge, sjuery     | |           :+:      :+:    :+:   */
#*     ___  __ _  __ _ _ __ | | __ _ _ __ | |_        +:+ +:+         +:+     */
#*    / _ \/ _` |/ _` | '_ \| |/ _` | '_ \| __|     +#+  +:+       +#+        */
#*   |  __/ (_| | (_| | |_) | | (_| | | | | |_    +#+#+#+#+#+   +#+           */
#*    \___|\__, |\__, | .__/|_|\__,_|_| |_|\__|       #+#   #+#               */
#*          __/ | __/ | |                            ###  ########.fr         */
#*         |___/ |___/|_|                                                     */
#* ************************************************************************** */

NAME	= corewar
ASMNAME = asm
DASMNAME = dasm

FILES	= 	main parse_file ncurses \
			read_bytes reg_ops op \
			vm_args flags init util vis \
			reg_util acb reset vm_op \
			vm_load vm_util jumptable \
			queue_utils read_utils
ASMFILES= 	main convert_to_hex op \
			parse print_binary
DASMFILES= 	disassembler convert_to_asmbly op \
			parse
#ASMSRC	= $(patsubst %, %.c, $(ASMFILES))
#ASMOBJ 	= $(addprefix ./objects/, $(ASMSRC:.c=.o))
#DASMSRC	= $(patsubst %, %.c, $(DASMFILES))
#DASMOBJ = $(addprefix ./objects/, $(DASMSRC:.c=.o))
SRC		= $(addprefix ./src/vm/, $(patsubst %, %.c, $(FILES)))
OBJ 	= $(addprefix ./objects/vm/, $(patsubst %, %.o, $(FILES)))
ASMSRC	= $(addprefix ./src/assembler/, $(patsubst %, %.c, $(ASMFILES)))
ASMOBJ 	= $(addprefix ./objects/assembler/, $(patsubst %, %.o, $(ASMFILES)))
DASMSRC		= $(addprefix ./src/dassembler/, $(patsubst %, %.c, $(DASMFILES)))
DASMOBJ 	= $(addprefix ./objects/dassembler/, $(patsubst %, %.o, $(DASMFILES)))
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=undefined #-fsanitize=address
#CFLAGS	= -g
IFLAGS	= -I libft/includes -I includes
#LFLAGS	= -L libft -lft -lcurses -Wl,-stack_size -Wl,0x1000000
LFLAGS = -L libft -lft -lcurses

.SILENT:

all: $(ASMNAME) $(NAME) $(DASMNAME)

$(DASMNAME): $(DASMOBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(DASMNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created DASM"

$(ASMNAME): $(ASMOBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(ASMNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created ASM"

$(NAME): $(OBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created Corewar"

./objects/%.o: ./src/%.c
	mkdir -p objects
	mkdir -p objects/vm
	mkdir -p objects/assembler
	mkdir -p objects/dassembler
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	make fclean -C libft/
	/bin/rm -f *.o
	/bin/rm -rf ./objects/*.o
	/bin/rm -rf ./objects/assembler/*.o
	/bin/rm -rf ./objects/dassembler/*.o
	/bin/rm -rf ./objects/vm/*.o
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned Corewar & ASM"

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)
	/bin/rm -f $(ASMNAME)
	/bin/rm -f $(DASMNAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned Corewar & ASM"

re: fclean all

.PHONY: clean fclean re all test
