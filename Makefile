##========== SOURCES ==========##

SRC = parse.c \
		struct_init.c \
		unleak.c \
		errors.c \
		fork.c
MAIN = pipex.c


##========== OBJECTS ==========##

OBJS = $(SRC:.c=.o)
MAIN_OBJ = $(MAIN:.c=.o)

##========== COLORS ==========##


BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== COMPILATOR ==========##

CC = clang

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(LIBS) -fsanitize=address
LIBS = -Llibft -lft
LIBFT = libft/libft.a

##========== NAMES ==========##

NAME = pipex

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	DEBUG_MODE = 1
endif

ifdef FAST
	J4 = -j4
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUM_LINES_TO_CLEAR = 1

all : $(CLEAR) $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MAIN_OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) $(MAIN_OBJ) $(OBJS) $(LDFLAGS)
	@echo "$(GREEN)Pipex compiled$(BASE_COLOR)"

$(LIBFT) :
	@DEBUG=$(DEBUG_MODE) TIMER=$(TIMER) IS_PRINT=$(IS_PRINT) $(MAKE) -C libft --no-print-directory $(J4)

clean :
	@rm -rf $(OBJS)
	@rm -rf $(MAIN_OBJ)
	@$(MAKE) -C libft clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) -C libft fclean --no-print-directory
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

%.o : %.c
##	@echo -e "\033[$(shell expr $(NUM_LINES_TO_CLEAR));H\033[K"
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)Compiling Pipex$(BASE_COLOR)"
	@echo "╔==============================================╗"
	@echo -n "║$(GREEN)"
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 45 - $(INDEX) \* 45 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║"
	@echo "╚==============================================╝"
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "Compiling : $<"
	$(CC) $(CFLAGS) -c $< -o $@
else
	@$(CC) $(CFLAGS) -c $< -o $@
endif



#bonus : all $(CHECKER)
#
#$(CHECKER) : $(OBJS) $(LIBFT) $(BONUS_MAIN_OBJ)
#		$(CC) -o $(CHECKER) $(CFLAGS) $(BONUS_MAIN_OBJ) $(OBJS) $(LDFLAGS)


.PHONY : all bonus clean fclean re
