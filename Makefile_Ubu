# -=-=-=-=-	NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
NAME			= minishell
MK			= Makefile

# -=-=-=-=-	CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

RESET		:= \033[0;39m
BLACK		:= \033[0;30m
RED			:= \033[0;91m
GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
MAGENTA		:= \033[0;95m
CYAN		:= \033[0;96m
GRAY		:= \033[0;90m
WHITE		:= \033[0;97m

# -=-=-=-=-	DIRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
SRC_DIR	= src/
OBJ_DIR	= obj/
INC_DIR	= hdrs/
LIB_DIR = libs/
RDL_DIR = $(LIB_DIR)readline/
LFT_DIR = $(LIB_DIR)libft/

# -=-=-=-=-	CMNDS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
CC			= gcc
SANS		= -fsanitize=address -g
CFLAGS		= -Wall -Werror -Wextra
AR			= ar -rcs
RM			= rm -f
MKDIR		= mkdir -p
CP			= cp -f
MAKE		= make -s
MUTE		= &> /dev/null
# -=-=-=-=-	LIBS/HEADERS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
LIBS		+= $(LFT_DIR)libft.a $(RDL_DIR)libreadline.a $(RDL_DIR)libhistory.a
HDRS		+= $(INC_DIR)minishell.h
# -=-=-=-=-	SOURCES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRCS		:= $(shell find src -name "*.c")

# -=-=-=-=-	OBJECTS/DEPENDENCIES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

#OBJS		:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))#@cd $(RDL_DIR) $(MUTE) && ./configure $(MUTE)
OBJS		:= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS		+= $(addsuffix .d, $(basename $(OBJS)))

# -=-=-=-=-	COMPILING -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
INCLUDE 	= -I$(INC_DIR)

all: $(NAME)

$(NAME):: $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(SANS) -L$(LFT_DIR) -L$(RDL_DIR) $(INCLUDE) $(OBJS) -o $(NAME) -lft -lreadline -lhistory -ltermcap
	echo "$(GREEN)🐜🐌MINISHELL COMPILED🐜🐌$(RESET)"

$(NAME)::
	echo "$(BLUE)Nothing to be done for $@$(RESET)";

$(LIBS):
	make -sC $(LFT_DIR) $(MUTE)
	make -sC $(RDL_DIR) $(MUTE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MK) $(HDRS)
	$(MKDIR) $(dir $@)
	echo "$(MAGENTA)Compiling: $<$(RESET)"
	$(CC) -MT $@ -MMD -MP $(INCLUDE) $(CFLAGS) $(SANS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -sC $(RDL_DIR)
	make clean -sC $(LFT_DIR)
	echo "$(CYAN)Dependencies and objects removed$(RESET)"

fclean: clean
	$(RM) $(NAME)
	make fclean -sC $(LFT_DIR)
	echo "$(RED)$(NAME) succesfully removed$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY:	all clean fclean re make_libs