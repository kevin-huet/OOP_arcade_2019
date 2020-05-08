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
BINARY_NAME	=	$(TARGET_DIR)$(BASE_NAME)sfml.so

SRC_FILES	=	$(CURRENT_DIR)sfml.cpp

SRC_OBJ		=	$(SRC_FILES:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -fPIC -I $(INCLUDE_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	compil

print_name:
	@$(ECHO) "███████╗███████╗███╗   ███╗██╗     "
	@$(ECHO) "██╔════╝██╔════╝████╗ ████║██║     "
	@$(ECHO) "███████╗█████╗  ██╔████╔██║██║     "
	@$(ECHO) "╚════██║██╔══╝  ██║╚██╔╝██║██║     "
	@$(ECHO) "███████║██║     ██║ ╚═╝ ██║███████╗"
	@$(ECHO) "╚══════╝╚═╝     ╚═╝     ╚═╝╚══════╝"

compil: print_name $(SRC_OBJ)
	$(CC) $(SRC_OBJ) $(CFLAGS) -o $(BINARY_NAME) -shared -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	$(RM) $(SRC_OBJ)

fclean:	clean
	$(RM) $(BINARY_NAME)

re: fclean all
