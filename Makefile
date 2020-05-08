##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

MAKE			=	make
RM_PRINT		=	--no-print-directory --no-print

ROOT_DIR		=	./
SRC_DIR			=	$(ROOT_DIR)src/
CORE_DIR		=	$(SRC_DIR)core/
GAMES_DIR		=	$(SRC_DIR)games/
GRAPHICALS_DIR	=	$(SRC_DIR)graphicals/

all:	compil

compil:
	@$(MAKE) -C $(CORE_DIR) all $(RM_PRINT)
	@$(MAKE) -C $(GAMES_DIR) all $(RM_PRINT)
	@$(MAKE) -C $(GRAPHICALS_DIR) all $(RM_PRINT)

core:
	@$(MAKE) -C $(CORE_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(CORE_DIR) all $(RM_PRINT)

games:
	@$(MAKE) -C $(GAMES_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(GAMES_DIR) all $(RM_PRINT)

graphicals:
	@$(MAKE) -C $(GRAPHICALS_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(GRAPHICALS_DIR) all $(RM_PRINT)

clean:
	@$(MAKE) -C $(CORE_DIR) clean $(RM_PRINT)
	@$(MAKE) -C $(GAMES_DIR) clean $(RM_PRINT)
	@$(MAKE) -C $(GRAPHICALS_DIR) clean $(RM_PRINT)

fclean:
	@$(MAKE) -C $(CORE_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(GAMES_DIR) fclean $(RM_PRINT)
	@$(MAKE) -C $(GRAPHICALS_DIR) fclean $(RM_PRINT)

re: fclean all

.PHONY: all compil core games graphicals clean fclean re