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
ASMSNAME = asms

FILES	= 	main parse_file ncurses \
			read_bytes op vis_highlight \
			vm_args flags init util vis \
			reg_util cycle reset vm_op \
			vm_load vm_util jumptable \
			queue_utils read_utils read_value \
			process_update queue acb write_utils
ASMFILES= 	main convert_to_hex op \
			parse print_binary save_label check_params
ASMSFILES 	=	main op disassembler/dasm disassembler/print_instructions
#ASMSRC	= $(patsubst %, %.c, $(ASMFILES))
#ASMOBJ 	= $(addprefix ./objects/, $(ASMSRC:.c=.o))
SRC		= $(addprefix ./src/vm/, $(patsubst %, %.c, $(FILES)))
OBJ 	= $(addprefix ./objects/vm/, $(patsubst %, %.o, $(FILES)))
ASMSSRC	= $(addprefix ./src/assemblers/, $(patsubst %, %.c, $(ASMSFILES)))
ASMSRC	= $(addprefix ./src/assembler/, $(patsubst %, %.c, $(ASMFILES)))
ASMOBJ 	= $(addprefix ./objects/assembler/, $(patsubst %, %.o, $(ASMFILES)))
ASMSOBJ = $(addprefix ./objects/assemblers/, $(patsubst %, %.o, $(ASMSFILES)))
CFLAGS	= -Wall -Wextra -Werror -g
#CFLAGS	= -g
IFLAGS	= -I libft/includes -I includes
#LFLAGS	= -L libft -lft -lcurses -Wl,-stack_size -Wl,0x1000000
LFLAGS = -L libft -lft -lcurses

.SILENT:

all: $(ASMNAME) $(ASMSNAME) $(NAME) $(DASMNAME)

$(DASMNAME): $(DASMOBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(DASMNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created DASM"

$(ASMNAME): $(ASMOBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(ASMNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created ASM"

$(ASMSNAME): $(ASMSOBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(ASMSNAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created ASMS"

$(NAME): $(OBJ)
	make -C libft/
	gcc $(CFLAGS) $(LFLAGS) $(IFLAGS) $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created Corewar"

./objects/%.o: ./src/%.c
	mkdir -p objects
	mkdir -p objects/vm
	mkdir -p objects/assembler
	mkdir -p objects/assemblers
	mkdir -p objects/assemblers/disassembler
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	make fclean -C libft/
	/bin/rm -f *.o
	/bin/rm -rf ./objects/*.o
	/bin/rm -rf ./objects/assembler/*.o
	/bin/rm -rf ./objects/assembler/assembler/*.o
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
