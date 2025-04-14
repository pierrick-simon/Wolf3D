##
## EPITECH PROJECT, 2025
## Wol3D
## File description:
## Makefile
##

SRC =

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -g3

NAMELIB = libmy.a

all:	$(NAMELIB)

$(NAMELIB):	$(OBJ)
	$(AR) rc $(NAMELIB) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAMELIB)

re:	fclean all

.PHONY: all clean fclean re
