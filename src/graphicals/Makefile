##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

MAKE			=	make
RM_PRINT		=	--no-print-directory --no-print

GRAPHICALS_DIR	=	./
LIB1_DIR		=	$(GRAPHICALS_DIR)sfml/
LIB2_DIR		=	$(GRAPHICALS_DIR)sdl/
LIB3_DIR		=	$(GRAPHICALS_DIR)ncurses/

all:	compil

compil:
	@$(MAKE) -C $(LIB1_DIR) all $(RM_PRINT)
	@$(MAKE) -C $(LIB2_DIR) all $(RM_PRINT)
	@$(MAKE) -C $(LIB3_DIR) all $(RM_PRINT)

clean:
	@$(MAKE) -C $(LIB1_DIR) clean $(RM_PRINT)
	@$(MAKE) -C $(LIB2_DIR) clean $(RM_PRINT)
	@$(MAKE) -C $(LIB3_DIR) clean $(RM_PRINT)

fclean:
	@$(MAKE) -C $(LIB1_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(LIB2_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(LIB3_DIR) fclean $(RM_PRINT)

re: fclean all

.PHONY: all compil clean fclean re