NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRC_DIR		=	src
SRC			=	$(wildcard $(SRC_DIR)/*c)
OBJ			=	$(SRC:%.c=%.o)

INC_DIR		=	include
HEADER		=	$(INC_DIR)/minishell.h

LIBFT_DIR	=	$(INC_DIR)/libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

RLINE_INCLUDE	= -I ~/.brew/Cellar/readline/8.2.1/include/
RLINE_L			= -L ~/.brew/Cellar/readline/8.2.1/lib/ -lreadline -lhistory

RM			=	rm -f

all:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@$(MAKE) --no-print-directory $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(OBJ) $(LIBFT_A) $(INC_FLAGS) -o $(NAME) $(RLINE_L)
# $(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(INC_FLAGS) -o $(NAME) $(RLINE_L)

%.o: %.c $(HEADER)
	$(CC) $(RLINE_INCLUDE) -c $< -o $@
# $(CC) $(CFLAGS) $(RLINE_INCLUDE) -c $< -o $@

clean:
	@make clean -sC $(LIBFT_DIR)
	$(RM) $(OBJ)
	@echo "clean"

fclean: clean
	$(RM) $(NAME)
	@echo "fclean"

re:	fclean all

.PHONY: all clean fclean re