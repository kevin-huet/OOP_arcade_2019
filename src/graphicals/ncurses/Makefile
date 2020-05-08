##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC			=	g++
RM			=	rm -f
ECHO		=	echo -e

ROOT_DIR	=	../../../
TARGET_DIR	=	$(ROOT_DIR)lib/
INCLUDE_DIR	=	../../include/
CURRENT_DIR	=	./

BASE_NAME	=	lib_arcade_
BINARY_NAME	=	$(TARGET_DIR)$(BASE_NAME)ncurses.so

SRC_FILES	=	$(CURRENT_DIR)ncurses.cpp

SRC_OBJ		=	$(SRC_FILES:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -fPIC -I $(INCLUDE_DIR) -lncurses

all:	compil

print_name:
	@$(ECHO) "███╗   ██╗ ██████╗██╗   ██╗██████╗ ███████╗███████╗███████╗"
	@$(ECHO) "████╗  ██║██╔════╝██║   ██║██╔══██╗██╔════╝██╔════╝██╔════╝"
	@$(ECHO) "██╔██╗ ██║██║     ██║   ██║██████╔╝███████╗█████╗  ███████╗"
	@$(ECHO) "██║╚██╗██║██║     ██║   ██║██╔══██╗╚════██║██╔══╝  ╚════██║"
	@$(ECHO) "██║ ╚████║╚██████╗╚██████╔╝██║  ██║███████║███████╗███████║"
	@$(ECHO) "╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"

compil: print_name $(SRC_OBJ)
	$(CC) $(SRC_OBJ) $(CXXFLAGS) -o $(BINARY_NAME) -shared

clean:
	$(RM) $(SRC_OBJ)

fclean:	clean
	$(RM) $(BINARY_NAME)

re: fclean all
