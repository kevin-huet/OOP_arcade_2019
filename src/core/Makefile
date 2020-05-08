##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC			=	g++
RM			=	rm -f
ECHO		=	echo -e

ROOT_DIR	=	../../
TARGET_DIR	=	$(ROOT_DIR)
INCLUDE_DIR	=	../include/
CURRENT_DIR	=	./
SRC_DIR		=	$(CURRENT_DIR)src/
SRC_INCLUDE	=	$(CURRENT_DIR)include/

BINARY_NAME	=	$(TARGET_DIR)arcade

SRC_FILES	=	$(SRC_DIR)main.cpp		\
				$(SRC_DIR)DLLoader.cpp	\
				$(SRC_DIR)Core.cpp

SRC_OBJ		=	$(SRC_FILES:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -fPIC -I $(INCLUDE_DIR) -I $(SRC_INCLUDE) -std=c++17

all:	compil

print_name:
	@$(ECHO) " █████╗ ██████╗  ██████╗ █████╗ ██████╗ ███████╗"
	@$(ECHO) "██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝"
	@$(ECHO) "███████║██████╔╝██║     ███████║██║  ██║█████╗  "
	@$(ECHO) "██╔══██║██╔══██╗██║     ██╔══██║██║  ██║██╔══╝  "
	@$(ECHO) "██║  ██║██║  ██║╚██████╗██║  ██║██████╔╝███████╗"
	@$(ECHO) "╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚═════╝ ╚══════╝"

compil: print_name $(SRC_OBJ)
	$(CC) $(SRC_OBJ) $(CFLAGS) -o $(BINARY_NAME) -ldl -std=c++17

clean:
	$(RM) $(SRC_OBJ)

fclean:	clean
	$(RM) $(BINARY_NAME)

re: fclean all