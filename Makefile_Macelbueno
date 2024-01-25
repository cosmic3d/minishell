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
CFLAGS		= -Wall -Werror -Wextra -g
AR			= ar -rcs
RM			= rm -f
MKDIR		= mkdir -p
CP			= cp -f
MAKE		= make -s
MUTE		= &> /dev/null
CR			= \033[K\r

#.ONESHELL:

# -=-=-=-=-	FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
# Function to hide the cursor
define hide_cursor
    @printf "\e[?25l"  # Hide the cursor
endef

# Function to show the cursor
define show_cursor
    @printf "\e[?25h"  # Show the cursor
endef
# -=-=-=-=-	LIBS/HEADERS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
LIBS		+= $(LFT_DIR)libft.a $(RDL_DIR)libreadline.a $(RDL_DIR)libhistory.a
HDRS		+= $(INC_DIR)*.h
# -=-=-=-=-	SOURCES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRCS		:= token_expansor  cmd_expansor_utils  token_expansor_utils  cmd_expansor  signal_handler  echo_chars\
unset_builtin cd_builtin  env_builtin export_utils  \
export_process_arg  export_builtin  echo_builtin  pwd_builtin  llamar_builtins\
exit_builtin  error  utils  minishell  debug  readline_loop  \
token_list_utils  env_list_utils_2  env_list_utils   env_list_init  generic_list_utils  cmd_parse_checker  \
cmd_parse  cmd_parse_brackets  cmd_env_creation  cmd_execute  cmd_struct  cmd_execute_utils  \
cmd_struct_utils  cmd_execute_redirections  find_filepath find_filepath_utils  cmd_execute_redirections_utils

SRCS		:=	$(addsuffix .c,$(SRCS))

vpath %.c src src/expansor src/general src/general/signals src/general/builtins src/general/builtins/unset src/general/builtins/cd \
src/general/builtins/env src/general/builtins/export src/general/builtins/echo src/general/builtins/pwd src/general/builtins/exit src/general/utils \
src/general/debug src/general/lists src/general/lists/env_list src/parser src/executor src/executor/get_pathname

# -=-=-=-=-	OBJECTS/DEPENDENCIES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #


OBJS		:= $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS		+= $(addsuffix .d, $(basename $(OBJS)))

# -=-=-=-=-	COMPILING -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
INCLUDE 	= -Ihdrs

all: $(NAME)

$(NAME):: $(LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(SANS) -ltermcap $(LIBS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)\n🐜🐌MINISHELL COMPILED🐜🐌$(RESET)\n"

$(NAME)::
	@printf "$(BLUE)Nothing to be done for $@\n$(RESET)";
	@$(show_cursor)

$(LIBS):
	@cd $(RDL_DIR) $(MUTE) && ./configure $(MUTE)
	@make -sC $(RDL_DIR) $(MUTE)
	@make -sC $(LFT_DIR) $(MUTE)

$(OBJ_DIR)%.o: %.c $(MK) $(HDRS)
	@$(hide_cursor)
	@$(MKDIR) $(dir $@)
	@printf "$(MAGENTA)Compiling: $(notdir $<)$(RESET)$(CR)"
	@$(CC) -MT $@ -MMD -MP $(INCLUDE) $(CFLAGS) $(SANS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -sC $(RDL_DIR)
	@make clean -sC $(LFT_DIR)
	@echo "$(CYAN)Dependencies and objects removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC $(LFT_DIR)
	@echo "$(RED)$(NAME) succesfully removed$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY:	all clean fclean re make_libs