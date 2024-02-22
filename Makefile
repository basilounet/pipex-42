##========== SOURCES ==========##

SRC = parse.c \
		struct_init.c \
		unleak.c \
		errors.c \
		fork.c
MAIN = pipex.c
#BONUS_MAIN = pipex_bonus.c


##========== OBJECTS ==========##

OBJS = $(SRC:.c=.o)
MAIN_OBJ = $(MAIN:.c=.o)
#BONUS_MAIN_OBJ = $(BONUS_MAIN:.c=.o)

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

CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = $(LIBS) -fsanitize=address
LIBS := -Llibft -lft
LIBFT = libft/libft.a

##========== NAMES ==========##

NAME = pipex

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MAIN_OBJ)
		$(CC) -o $(NAME) $(CFLAGS) $(MAIN_OBJ) $(OBJS) $(LDFLAGS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@$(MAKE) -C libft --no-print-directory -j4

#bonus : all $(CHECKER)
#
#$(CHECKER) : $(OBJS) $(LIBFT) $(BONUS_MAIN_OBJ)
#		$(CC) -o $(CHECKER) $(CFLAGS) $(BONUS_MAIN_OBJ) $(OBJS) $(LDFLAGS)

clean :
	@rm -rf $(OBJS)
	@rm -rf $(MAIN_OBJ)
#	@rm -rf $(BONUS_MAIN_OBJ)
	@$(MAKE) -C libft clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
#	@rm -rf $(CHECKER)
	@$(MAKE) -C libft fclean --no-print-directory
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

.PHONY : all bonus clean fclean re
