##
## EPITECH PROJECT, 2025
## Wolf3D
## File description:
## Makefile
##

SRC = 	my_str_to_word_array.c	\
		open_file.c	\
		array.c	\
		is_int_float.c	\
		get_nblen.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra

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
