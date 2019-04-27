# 42-Corewar

Corewar is a project where we have to design an assembler (to compile champions to fight in the game), the virtual machine (the arena memory space where champions fight), and a champion (because why not?) to battle it out in a virtual space of memory

## Corewar with Visualizer

![alt text](https://raw.githubusercontent.com/sjuery/42-Corewar/master/image/visualizer.gif)

## Description

Corewar is a very peculiar game. It’s about bringing players together around a
virtual machine, which will load some champions who will fight against one another
with the support of processes, with the objective being for these champions
to stay alive.

The processes are executed sequentially within the same virtual machine and memory
space. They can therefore, among other things, write and rewrite on top of
each others so to corrupt one another, force the others to execute instructions that
can damage them, try to rewrite on the go.

The game ends when all the processes are dead. The winner is the last player
reported to be alive.

## Workload

The project is one of the capstone project for 42. Project design was as followed:
1) project was first divided up, where aneeshnazar & mlu worked on the VM, and sjuery & isahodge focused on the ASM
2) isahodge moved onto the VM later where sjuery finish ASM, mlu & aneeshnazar continued on VM
3) sjuery moved onto the disassembler (converting the binary back into assembly code), and we all finalized the VM
4) two champions were written, Lydeka by mlu, and zork (one of the test champions we needed to beat) by aneeshnazar
5) multiple refactoring of the project was done over time in order to optimize and improve the VM

### Prerequisites

No Prerequisites needed for this project (Most library functions were self written and can be found in the libft folder)

### Installing

This Makefile has multiple instructions:

> ASM (Assembler), Corewar (Virtual Machine), DASM (Disassembler)
```
make asm
[ ✔ ] Created ASM
make corewar
[ ✔ ] Created Corewar
make dasm
[ ✔ ] Created DASM
```
Simply typing "make" will create all 3 executables

```
make
[ ✔ ] Created ASM
[ ✔ ] Created Corewar
[ ✔ ] Created DASM
```

## Running the executables

### ASM

ASM takes a file written is Assembly (Terminating with .s). And turns it into a binary file readable by the Virtual Machine.
Once the executable is run with a valid file, a .cor file is created/edit with the same name.

```
./asm
Usage: ./asm <sourcefile.s>
./asm sourcefile.s
Writing to .cor file
```
### DASM

DASM takes a binary file (Terminating with .cor). And turns it back into Assembly so it can be improved.
Once the executable is run with a valid file, a .s file is created/edited with the same name.

```
./dasm
Usage: ./dasm <sourcefile.cor>
./dasm sourcefile.cor
Writing to .s file
```
### Virtual Machine

The Virtual Machine takes the binary of each champions (4 max) and puts them up against each other in a set memory space. Allowing them to rewrite that memory space and get it to execute specific instructions to eliminate the other and force it to hurt itself.

None of the '-' options are required to run the code, however -g is recommended in order to see what is going on.

```
./corewar 
Corewar Usage
./corewar { d <value> | g | b | r | s <value> | i } { n <value> | champion.cor }
-dump, -d			    dump mode
-graphic, -g			graphic mode
-debug, -b			  debug mode
-rainbow, -r			special rainbow mode (only in graphic)
-sound, -s			  sound on (1 spawn, 2 death, 3 all)
-number, -n			  designate champ slot (valid 1-4)
-intro, -i			  toggle voice intro
./corewar resources/champs/Octobre_Rouge_V4.2.cor resources/jumper.cor
 ██████╗ ██████╗ ██████╗ ███████╗██╗    ██╗ █████╗ ██████╗      ██████╗██╗  ██╗ █████╗ ███╗   ███╗██████╗ ██╗ ██████╗ ███╗   ██╗███████╗
██╔════╝██╔═══██╗██╔══██╗██╔════╝██║    ██║██╔══██╗██╔══██╗    ██╔════╝██║  ██║██╔══██╗████╗ ████║██╔══██╗██║██╔═══██╗████╗  ██║██╔════╝
██║     ██║   ██║██████╔╝█████╗  ██║ █╗ ██║███████║██████╔╝    ██║     ███████║███████║██╔████╔██║██████╔╝██║██║   ██║██╔██╗ ██║███████╗
██║     ██║   ██║██╔══██╗██╔══╝  ██║███╗██║██╔══██║██╔══██╗    ██║     ██╔══██║██╔══██║██║╚██╔╝██║██╔═══╝ ██║██║   ██║██║╚██╗██║╚════██║
╚██████╗╚██████╔╝██║  ██║███████╗╚███╔███╔╝██║  ██║██║  ██║    ╚██████╗██║  ██║██║  ██║██║ ╚═╝ ██║██║     ██║╚██████╔╝██║ ╚████║███████║
 ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
Introducing contestants...
* Player 1, weighing 604 bytes, "Octobre Rouge V4.2 longer" ("\") !
* Player 2, weighing 323 bytes, "Jumper !" ("Cen fait C lforker !") !
```

## Authors

* **Michael Lu** - (https://github.com/lunairi)
* **Stanislas Juery** - (https://github.com/sjuery)
* **Isa Hodge** - (https://github.com/isahodge)
* **Aneesh Nazar** - (https://github.com/aneeshnazar)
