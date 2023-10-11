NAME	=	libft.a

SRC		=	$(wildcard *.c)

OBJECTS =	$(SRC:%.c=%.o)

HEADER	=	libft.h

CC		=	gcc
CCFLAGS =	-Wall -Werror -Wextra
ARFLAGS	=	rcs

RM		=	@rm -f

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJECTS)
	@ar $(ARFLAGS) $(NAME) $(OBJECTS)
	@echo "'libft.a' created/updated succesfully"

%.o: %.c $(HEADER)
	$(CC) $(CCFLAGS) -c $< -o $@

objects: $(OBJECTS)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all objects clean fclean re