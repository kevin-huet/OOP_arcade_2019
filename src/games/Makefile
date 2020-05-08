##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

MAKE			=	make
RM_PRINT		=	--no-print-directory --no-print

GAMES_DIR		=	./
GAME1_DIR		=	$(GAMES_DIR)nibbler/
GAME2_DIR		=	$(GAMES_DIR)pacman/

all:	compil

compil:
	@$(MAKE) -C $(GAME1_DIR) all $(RM_PRINT)
	@$(MAKE) -C $(GAME2_DIR) all $(RM_PRINT)

clean:
	@$(MAKE) -C $(GAME1_DIR) clean $(RM_PRINT)
	@$(MAKE) -C $(GAME2_DIR) clean $(RM_PRINT)

fclean:
	@$(MAKE) -C $(GAME1_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(GAME2_DIR) fclean $(RM_PRINT)

re: fclean all

.PHONY: all compil clean fclean re